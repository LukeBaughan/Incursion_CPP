// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Incursion.h"

AGM_Incursion::AGM_Incursion()
{
	GameInstance = nullptr;

	DefaultPawnClass = nullptr;
	PlayerManager = nullptr;
	UI_Manager = nullptr;

	PlayerControllerClass = APC_PlayerController::StaticClass();
}

void AGM_Incursion::BeginPlay()
{
	ExecutePreGameFunctions();
}

void AGM_Incursion::ExecutePreGameFunctions()
{
	GameInstance = Cast<UGI_Incursion>(GetGameInstance());

	SpawnPlayerManager();
	SetUpPlayerManager();
	SetUpUI_Manager();
	PlayerManager->SetUpEventDispatchers();
}


void AGM_Incursion::SpawnPlayerManager()
{
	PlayerManager = GetWorld()->SpawnActor<AA_PlayerManager>(FVector::Zero(), FRotator::ZeroRotator);
}

void AGM_Incursion::SetUpPlayerManager()
{
	if(PlayerManager)
		PlayerManager->Initialise(GameInstance->GetSpawnWeaponClass());
	else
		UE_LOG(LogTemp, Error, TEXT("GM_Incursion: PlayerManager Invalid"));
}

// Spawns and sets up the UI manager 
void AGM_Incursion::SetUpUI_Manager()
{
	UI_Manager = GetWorld()->SpawnActor<AA_UI_Manager>(FVector::Zero(), FRotator::ZeroRotator);

	if (UI_Manager)
		UI_Manager->Initialise(PlayerManager->PlayerController);
	else
		UE_LOG(LogTemp, Error, TEXT("GM_Incursion: UI_Manager Invalid"));

	PlayerManager->WidgetHUD = UI_Manager->WidgetHUD;
}