
#include "GM_Incursion.h"

#include "Kismet/Gameplaystatics.h"

AGM_Incursion::AGM_Incursion() :
	SettingsManager(nullptr),
	GameInstance(nullptr),
	StatsManager(nullptr),
	StoreManager(nullptr),
	PlayerManager(nullptr),
	UI_Manager(nullptr),
	WaveManager(nullptr),
	Lives(2)
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = APC_PlayerController::StaticClass();
}

void AGM_Incursion::BeginPlay()
{
	ExecutePreGameFunctions();
	ExecuteInGameFunctions();
}

void AGM_Incursion::ExecutePreGameFunctions()
{
	GameInstance = Cast<UGI_Incursion>(GetGameInstance());

	SetUpStatsManager();
	SpawnStoreManager();

	SpawnPlayerManager();
	SetUpPlayerManager();
	SetUpUI_Manager();
	SetUpSettingsManager();

	SetUpWaveManager();
	PlayerManager->SetUpEventDispatchers(StatsManager, StoreManager, WaveManager);
	SetUpStoreManager();
}


void AGM_Incursion::SetUpStatsManager()
{
	StatsManager = GetWorld()->SpawnActor<AA_StatsManager>();
	StatsManager->Initialise();
}

void AGM_Incursion::SpawnStoreManager()
{
	StoreManager = GetWorld()->SpawnActor<AA_StoreManager>();
}

void AGM_Incursion::SpawnPlayerManager()
{
	PlayerManager = GetWorld()->SpawnActor<AA_PlayerManager>();
}

void AGM_Incursion::SetUpPlayerManager()
{
	if (PlayerManager)
	{
		PlayerManager->Initialise(GameInstance->GetSpawnWeaponClass());
		PlayerManager->RequestTogglePauseGame.AddDynamic(this, &AGM_Incursion::TogglePauseGame);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GM_Incursion: PlayerManager Invalid"));
	}
}

// Spawns and sets up the UI manager 
void AGM_Incursion::SetUpUI_Manager()
{
	UI_Manager = GetWorld()->SpawnActor<AA_UI_Manager>();

	if (UI_Manager)
	{
		UI_Manager->Initialise(PlayerManager->PlayerController);
		UI_Manager->RequestTogglePauseGame.AddDynamic(this, &AGM_Incursion::TogglePauseGame);
		UI_Manager->RequestRestartGame.AddDynamic(this, &AGM_Incursion::RestartGame);
		UI_Manager->RequestMainMenu.AddDynamic(this, &AGM_Incursion::OpenMainMenu);
		UI_Manager->RequestCheckCanPurchaseTower.AddDynamic(StoreManager, &AA_StoreManager::CheckCanPurchaseTower);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GM_Incursion: UI_Manager Invalid"));
	}

	PlayerManager->WidgetHUD = UI_Manager->WidgetHUD;

	UI_Manager->WidgetHUD->WidgetLives->SetLives(Lives);
}

void AGM_Incursion::SetUpSettingsManager()
{
	SettingsManager = GetWorld()->SpawnActor<AA_SettingsManager>(AA_SettingsManager::StaticClass());
	SettingsManager->Initialise(UI_Manager->WidgetOptionsMenu);
}

void AGM_Incursion::SetUpWaveManager()
{
	WaveManager = GetWorld()->SpawnActor<AA_WaveManager>();
	WaveManager->Initialise(UI_Manager->WidgetHUD->WidgetTimer, UI_Manager->WidgetHUD->WidgetSkipCountdown);
	WaveManager->OnRequestLoseLives.AddDynamic(this, &AGM_Incursion::LoseLives);
	WaveManager->OnRequestPoints.AddDynamic(StoreManager, &AA_StoreManager::AddPoints);
	WaveManager->OnEnemyDefeatedDelegate.AddDynamic(StatsManager, &AA_StatsManager::IncrementEnemiesKilled);
	WaveManager->OnWaveBegin.AddDynamic(UI_Manager->WidgetHUD->WidgetWave, &UW_HUD_Wave::SetWave);
	WaveManager->OnWaveEnded.AddDynamic(PlayerManager, &AA_PlayerManager::ReplenishPlayerHealth);
	WaveManager->OnWaveEnded.AddDynamic(StoreManager, &AA_StoreManager::AddNewWavePoints);
	WaveManager->OnGameWon.AddDynamic(this, &AGM_Incursion::OnGameWon);
}

void AGM_Incursion::SetUpStoreManager()
{
	StoreManager->Initialise(UI_Manager, PlayerManager->PlayerCharacter->TowerPreviewLocation);
	StoreManager->OnRequestSetPlayerHoldingTower.AddDynamic(PlayerManager->PlayerCharacter, &AC_Player::SetCurrentlyHoldingTower);
	StoreManager->OnPointsAdded.AddDynamic(StatsManager, &AA_StatsManager::IncreaseTotalPoints);
}

void AGM_Incursion::ExecuteInGameFunctions()
{
	WaveManager->BeginWaveCountdown();
}

void AGM_Incursion::TogglePauseGame(bool Pause)
{
	UGameplayStatics::SetGamePaused(GetWorld(), Pause);
	UI_Manager->ToggleMenu(UI_Manager->WidgetPauseMenu);
}

void AGM_Incursion::RestartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Level_2"), true);
}

void AGM_Incursion::OpenMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Level_Dev"), true);
}

// Shows the win screen if the player finishes all waves
void AGM_Incursion::OnGameWon()
{
	if (Lives > 0)
	{
		StatsManager->IncrementGamesWon();
		UI_Manager->ShowWinScreen();	
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void AGM_Incursion::LoseLives(uint8 Amount)
{
	Lives -= Amount;

	if (Lives <= 0)
	{
		// Displays the lose screen when the player is out of lives
		StatsManager->IncrementGamesPlayed();
		UI_Manager->ShowLoseScreen();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	} 
	else
	{
		UI_Manager->WidgetHUD->WidgetLives->SetLives(Lives);
	}
}	