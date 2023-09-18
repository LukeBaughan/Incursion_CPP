// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "P_PlayerCamera.h"
#include "BFL_Incursion.h"
#include "W_MainMenu.h"
#include "W_Credits.h"

#include "GM_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class INCURSION_CPP_API AGM_MainMenu : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGM_MainMenu();

private:

	APlayerController* PlayerController;


	// Main Menu
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_MainMenu> WidgetMainMenuClass;
	// Widget Instance
	UPROPERTY()
		class UW_MainMenu* WidgetMainMenu;

	// Credits Menu
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_Credits> WidgetCreditsClass;
	// Widget Instance
	UPROPERTY()
		class UW_Credits* WidgetCredits;


	virtual void BeginPlay();

	void SetUpMenus();

	UFUNCTION()
	void OpenMenu(UUserWidget* CurrentMenu, MenuType MenuToOpen);

	UFUNCTION()
	void QuitGame();

};
