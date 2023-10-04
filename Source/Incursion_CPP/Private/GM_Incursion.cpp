// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Incursion.h"

AGM_Incursion::AGM_Incursion()
{
	GameInstance = nullptr;

	DefaultPawnClass = nullptr;
	PlayerManager = nullptr;
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
}


void AGM_Incursion::SpawnPlayerManager()
{
	PlayerManager = GetWorld()->SpawnActor<AA_PlayerManager>(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
}

void AGM_Incursion::SetUpPlayerManager()
{
	PlayerManager->Initialise(GameInstance->GetSpawnWeaponClass());
}