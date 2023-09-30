// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "A_PlayerManager.h"
#include "C_Player.h"
#include "PC_PlayerController.h"
#include "A_Gun.h"

#include "GM_Incursion.generated.h"

/**
 * 
 */
UCLASS()
class AGM_Incursion : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGM_Incursion();

protected:
	virtual void BeginPlay();

private:
	AA_PlayerManager* PlayerManager;

	void ExecutePreGameFunctions();

	void SpawnPlayerManager();
	void SetUpPlayerManager();
};
