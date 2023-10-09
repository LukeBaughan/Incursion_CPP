// Fill out your copyright notice in the Description page of Project Settings.


#include "A_PlayerManager.h"
#include "W_HUD_Ammo.h"

// Sets default values
AA_PlayerManager::AA_PlayerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerController = nullptr;
	PlayerCharacter = nullptr;

	SpawnPoint = nullptr;
	PlayerSpawnLocation = FVector::Zero();

	PlayerSpawnWeaponClass = nullptr;

	static ConstructorHelpers::FClassFinder<AC_Player> PlayerBP_ClassFinder(TEXT("/Game/Luke/Player/C_PlayerBP"));
	if (PlayerBP_ClassFinder.Succeeded())
		PlayerBP_Class = PlayerBP_ClassFinder.Class;
}

// Called when the game starts or when spawned
void AA_PlayerManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AA_PlayerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AA_PlayerManager::Initialise(TSubclassOf<class AA_Gun> SpawnWeapon) 
{
	PlayerCharacter = nullptr;
	PlayerSpawnWeaponClass = SpawnWeapon;

	SetUpPlayerController();
	SetUpPlayer();
}

void AA_PlayerManager::SetUpPlayerController()
{
	// Gets a referance to the first player controller found
	PlayerController = Cast<APC_PlayerController>(UGameplayStatics::GetActorOfClass(GetWorld(), APC_PlayerController::StaticClass()));

	if (PlayerController)
	{
		FInputModeGameOnly PlayerInputMode;
		PlayerController->SetInputMode(PlayerInputMode);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Player Controller not Found (In Player Manager)")));
	}

}

void AA_PlayerManager::SetUpPlayer()
{
	// Gets a reference to the first spawn point found
	SpawnPoint = Cast<ASpawnPoint>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnPoint::StaticClass()));

	if (SpawnPoint)
	{
		// Sets the spawn location to the spawn point's location
		PlayerSpawnLocation = SpawnPoint->GetActorLocation();
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("%f"), PlayerSpawnLocation.X));

		// Spawns and inits the player character at the spawn location
		PlayerSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		PlayerCharacter = GetWorld()->SpawnActor<AC_Player>(PlayerBP_Class, PlayerSpawnLocation, FRotator::ZeroRotator, PlayerSpawnParameters);
	
		if(PlayerCharacter)
			PlayerCharacter->Initialise(PlayerSpawnWeaponClass);
		else
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Player Character NULL")));

		// If theres a valid player character and controller, make the controller possess the character
		if (PlayerCharacter && PlayerController)
			PlayerController->Possess(PlayerCharacter);
		else
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Player Controller or Character NULL")));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Spawn Point NULL")));
}

void AA_PlayerManager::SetUpEventDispatchers()
{
	// Updates the ammo count when the player reloads/ shoots
	PlayerCharacter->OnAmmoAmountChanged.AddDynamic(WidgetHUD->WidgetAmmo, &UW_HUD_Ammo::SetAmmoAmount);
	PlayerCharacter->CallOnAmmoAmountChangedED();
}