
#include "A_PlayerManager.h"

#include "Kismet/GameplayStatics.h"
#include "W_HUD_Ammo.h"

// Sets default values
AA_PlayerManager::AA_PlayerManager() :
	PlayerController(Cast<APC_PlayerController>(UGameplayStatics::GetActorOfClass(GetWorld(), APC_PlayerController::StaticClass()))),
	PlayerCharacter(nullptr),

	SpectatorCamera(Cast<AA_SpectatorCamera>(UGameplayStatics::GetActorOfClass(GetWorld(), AA_SpectatorCamera::StaticClass()))),
	CameraSwitchBlendTime(3.0f),
	PlayerRespawnTime(5.0f),

	SpawnPoint(Cast<ASpawnPoint>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnPoint::StaticClass()))),
	PlayerSpawnLocation(FVector::Zero()),
	PlayerSpawnWeaponClass(nullptr)
{
	static ConstructorHelpers::FClassFinder<AC_Player> PlayerBP_ClassFinder(TEXT("/Game/Luke/Player/C_PlayerBP"));
	if (PlayerBP_ClassFinder.Succeeded())
		PlayerBP_Class = PlayerBP_ClassFinder.Class;
}

void AA_PlayerManager::Initialise(TSubclassOf<class AA_Gun> SpawnWeapon)
{
	PlayerSpawnWeaponClass = SpawnWeapon;

	SetUpPlayerController();
	SetUpPlayer();
}

void AA_PlayerManager::SetUpPlayerController()
{
	if (PlayerController)
	{
		FInputModeGameOnly PlayerInputMode;
		PlayerController->SetInputMode(PlayerInputMode);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("A_PlayerManager: Unable to get PlayerController"));
	}
}

void AA_PlayerManager::SetUpPlayer()
{
	if (SpawnPoint)
	{
		// Sets the spawn location to the spawn point's location
		PlayerSpawnLocation = SpawnPoint->GetActorLocation();
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("%f"), PlayerSpawnLocation.X));

		// Spawns and inits the player character at the spawn location
		PlayerSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		PlayerCharacter = GetWorld()->SpawnActor<AC_Player>(PlayerBP_Class, PlayerSpawnLocation, FRotator::ZeroRotator, PlayerSpawnParameters);

		if (PlayerCharacter)
		{
			PlayerCharacter->Initialise(PlayerSpawnWeaponClass);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("A_PlayerManager: Unable to get PlayerCharacter"));
		}

		// If theres a valid player character and controller, make the controller possess the character
		if (PlayerCharacter && PlayerController)
		{
			PlayerController->Possess(PlayerCharacter);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("A_PlayerManager: Unable to get PlayerCharacter or PlayerController"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("A_PlayerManager: Unable to get SpawnPoint"));
	}
}

void AA_PlayerManager::SetUpEventDispatchers(AA_WaveManager* WaveManager)
{
	// Updates the player's health bar when they take damage
	WidgetHUD->WidgetHealthBar->SetHealthBarAmount(PlayerCharacter->MaxHealth, PlayerCharacter->MaxHealth);
	PlayerCharacter->OnDamageTaken.AddDynamic(WidgetHUD->WidgetHealthBar, &UW_HUD_HealthBar::SetHealthBarAmount);

	//Switches cameras when the player dies
	PlayerCharacter->OnDead.AddDynamic(this, &AA_PlayerManager::EnterDeadPhase);

	PlayerCharacter->RequestPauseGame.AddDynamic(this, &AA_PlayerManager::RequestTogglePauseGameFunction);
	PlayerCharacter->RequestSkipCountdown.AddDynamic(WaveManager, &AA_WaveManager::SkipCountdown);

	// Updates the ammo count when the player reloads/ shoots
	PlayerCharacter->OnAmmoAmountChanged.AddDynamic(WidgetHUD->WidgetAmmo, &UW_HUD_Ammo::SetAmmoAmount);
	PlayerCharacter->CallOnAmmoAmountChangedED();
}

void AA_PlayerManager::RequestTogglePauseGameFunction(bool Pause)
{
	RequestTogglePauseGame.Broadcast(Pause);
}

// Switches the view to the spectator camera while the player is respawning
void AA_PlayerManager::EnterDeadPhase()
{
	SwitchToSpectatorCamera();

	GetWorldTimerManager().SetTimer(TH_PlayerDead, this, &AA_PlayerManager::RespawnPlayer, PlayerRespawnTime, false);
}

// Hides HUD + player mesh, Disables input and changes the camera to the spactate camera
void AA_PlayerManager::SwitchToSpectatorCamera()
{
	WidgetHUD->SetVisibility(ESlateVisibility::Collapsed);
	PlayerCharacter->IsDead = true;
	PlayerCharacter->CapsuleCollider->SetVisibility(false, true);
	PlayerController->SetViewTargetWithBlend(SpectatorCamera, CameraSwitchBlendTime, EViewTargetBlendFunction::VTBlend_Cubic);
}

// Teleports the player back to thier spawn and changes the camera to the player character's camera
void AA_PlayerManager::RespawnPlayer()
{
	PlayerCharacter->CapsuleCollider->SetWorldLocationAndRotation(PlayerSpawnLocation, FRotator::ZeroRotator);
	PlayerController->SetViewTargetWithBlend(PlayerCharacter, CameraSwitchBlendTime, EViewTargetBlendFunction::VTBlend_Cubic);
	ReplenishPlayerHealth();

	GetWorldTimerManager().SetTimer(TH_PlayerRespawning, this, &AA_PlayerManager::EnablePlayer, CameraSwitchBlendTime, false);
}

// Shows HUD + player mesh, Disables Movement 
void AA_PlayerManager::EnablePlayer()
{
	WidgetHUD->SetVisibility(ESlateVisibility::Visible);
	PlayerCharacter->IsDead = false;
	PlayerCharacter->CapsuleCollider->SetVisibility(true, true);

	GetWorldTimerManager().ClearTimer(TH_PlayerRespawning);
	GetWorldTimerManager().ClearTimer(TH_PlayerDead);
}

void AA_PlayerManager::ReplenishPlayerHealth()
{
	PlayerCharacter->CurrentHealth = PlayerCharacter->MaxHealth;
	PlayerCharacter->OnDamageTaken.Broadcast(PlayerCharacter->CurrentHealth, PlayerCharacter->MaxHealth);
}