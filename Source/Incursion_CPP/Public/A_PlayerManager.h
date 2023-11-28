// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "A_SpectatorCamera.h"
#include "A_StatsManager.h"
#include "A_StoreManager.h"
#include "A_UI_Manager.h"
#include "A_WaveManager.h"
#include "C_Player.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "PC_PlayerController.h"
#include "SpawnPoint.h"
#include "W_HUD.h"

#include "A_PlayerManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerManager_RequestTogglePauseGame, bool, PauseGame);

UCLASS()
class INCURSION_CPP_API AA_PlayerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_PlayerManager();

	void Initialise(TSubclassOf<class AA_Gun> SpawnWeapon);
	void SetUpEventDispatchers(AA_StatsManager* StatsManager, AA_StoreManager* StoreManager, AA_WaveManager* WaveManager);

	UFUNCTION()
		void ReplenishPlayerHealth();

	FPlayerManager_RequestTogglePauseGame RequestTogglePauseGame;

	AC_Player* PlayerCharacter;
	APC_PlayerController* PlayerController;
	UW_HUD* WidgetHUD;

	bool IsGameOver;

private:	
	void SetUpPlayerController();
	void SetUpPlayer();
	void SwitchToSpectatorCamera();
	void RespawnPlayer();
	void EnablePlayer();

	UFUNCTION()
		void RequestTogglePauseGameFunction(bool Pause);

	UFUNCTION()
		void EnterDeadPhase();

	AA_SpectatorCamera* SpectatorCamera;
	float CameraSwitchBlendTime;
	FTimerHandle TH_PlayerDead;
	FTimerHandle TH_PlayerRespawning;
	float PlayerRespawnTime;

	TSubclassOf<class AC_Player> PlayerBP_Class;

	ASpawnPoint* SpawnPoint;
	FVector PlayerSpawnLocation;
	FActorSpawnParameters PlayerSpawnParameters;

	TSubclassOf<class AA_Gun> PlayerSpawnWeaponClass;
};
