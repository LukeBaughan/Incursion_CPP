// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Incursion.h"

AGM_Incursion::AGM_Incursion()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = APC_PlayerController::StaticClass();
}

void AGM_Incursion::BeginPlay()
{
	playerManager = GetWorld()->SpawnActor<AA_PlayerManager>(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	playerManager->Initialise();
}