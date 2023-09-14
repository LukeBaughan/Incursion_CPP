// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "P_PlayerCamera.h"

#include "GM_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class INCURSION_CPP_API AGM_MainMenu : public AGameModeBase
{
	GENERATED_BODY()
	
private:

	APlayerController* PlayerController;

	virtual void BeginPlay();

};
