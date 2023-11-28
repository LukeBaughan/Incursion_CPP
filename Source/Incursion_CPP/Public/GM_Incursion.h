// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "A_Gun.h"
#include "A_PlayerManager.h"
#include "A_SettingsManager.h"
#include "A_StatsManager.h"
#include "A_StoreManager.h"
#include "A_UI_Manager.h"
#include "A_WaveManager.h"
#include "C_Player.h"
#include "GameFramework/GameModeBase.h"
#include "GI_Incursion.h"
#include "PC_PlayerController.h"

#include "GM_Incursion.generated.h"

UCLASS()
class AGM_Incursion : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGM_Incursion();

protected:
	virtual void BeginPlay();

private:
	void ExecutePreGameFunctions();

	void SetUpStatsManager();
	void SpawnStoreManager();
	void SpawnPlayerManager();
	void SetUpPlayerManager();
	void SetUpUI_Manager();
	void SetUpSettingsManager();
	void SetUpWaveManager();
	void SetUpStoreManager();

	void ExecuteInGameFunctions();

	UFUNCTION()
		void TogglePauseGame(bool Pause);

	UFUNCTION()
		void RestartGame();	
	
	UFUNCTION()
		void OpenMainMenu();

	UFUNCTION()
		void OnGameWon();

	UFUNCTION()
		void LoseLives(uint8 Amount);

	UGI_Incursion* GameInstance;

	AA_SettingsManager* SettingsManager;
	AA_StatsManager* StatsManager;
	AA_StoreManager* StoreManager;
	AA_PlayerManager* PlayerManager;
	AA_UI_Manager* UI_Manager;
	AA_WaveManager* WaveManager;

	int Lives;
	bool IsGameOver;
};
