// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "A_Gun.h"
#include "A_PlayerManager.h"
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

	void SpawnPlayerManager();
	void SetUpPlayerManager();
	void SetUpUI_Manager();
	void SetUpWaveManager();

	void ExecuteInGameFunctions();

	UFUNCTION()
		void LoseLives(uint8 Amount);

	UGI_Incursion* GameInstance;
	AA_PlayerManager* PlayerManager;
	AA_UI_Manager* UI_Manager;
	AA_WaveManager* WaveManager;

	int Lives;
};
