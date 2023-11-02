// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Incursion.h"

AGM_Incursion::AGM_Incursion() :
	GameInstance(nullptr),
	PlayerManager(nullptr),
	UI_Manager(nullptr),
	WaveManager(nullptr),
	Lives(100)
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

	SpawnPlayerManager();
	SetUpPlayerManager();
	SetUpUI_Manager();
	SetUpWaveManager();
	PlayerManager->SetUpEventDispatchers();
}


void AGM_Incursion::SpawnPlayerManager()
{
	PlayerManager = GetWorld()->SpawnActor<AA_PlayerManager>(FVector::Zero(), FRotator::ZeroRotator);
}

void AGM_Incursion::SetUpPlayerManager()
{
	if (PlayerManager)
	{
		PlayerManager->Initialise(GameInstance->GetSpawnWeaponClass());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GM_Incursion: PlayerManager Invalid"));
	}
}

// Spawns and sets up the UI manager 
void AGM_Incursion::SetUpUI_Manager()
{
	UI_Manager = GetWorld()->SpawnActor<AA_UI_Manager>(FVector::Zero(), FRotator::ZeroRotator);

	if (UI_Manager)
	{
		UI_Manager->Initialise(PlayerManager->PlayerController);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GM_Incursion: UI_Manager Invalid"));
	}

	PlayerManager->WidgetHUD = UI_Manager->WidgetHUD;

	UI_Manager->WidgetHUD->WidgetLives->SetLives(Lives);
}

void AGM_Incursion::SetUpWaveManager()
{
	WaveManager = GetWorld()->SpawnActor<AA_WaveManager>(FVector::Zero(), FRotator::ZeroRotator);
	//WaveManager->Initialise();
	WaveManager->OnRequestLoseLives.AddDynamic(this, &AGM_Incursion::LoseLives);
}

void AGM_Incursion::ExecuteInGameFunctions()
{
	WaveManager->BeginWaveCountdown();
}

void AGM_Incursion::LoseLives(uint8 Amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("GM_Incursion: Lives Before: %d"), Lives));
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("GM_Incursion: Lost %d Lives"), Amount));

	Lives -= Amount;

	if (Lives <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("GM_Incursion: Game Over!")));
	} 
	else
	{
		UI_Manager->WidgetHUD->WidgetLives->SetLives(Lives);	
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("GM_Incursion: Lives After: %d"), Lives));
	}
}	