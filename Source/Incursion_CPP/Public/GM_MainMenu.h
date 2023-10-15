// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BFL_Incursion.h"
#include "GameFramework/GameModeBase.h"
#include "GI_Incursion.h"
#include "P_PlayerCamera.h"
#include "W_Controls.h"
#include "W_Credits.h"
#include "W_MainMenu.h"
#include "W_WeaponSelect.h"

#include "GM_MainMenu.generated.h"

UCLASS()
class INCURSION_CPP_API AGM_MainMenu : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGM_MainMenu();

private:
	virtual void BeginPlay();

	void SetUpMenus();
	void SetUpMenusTest();

	UFUNCTION()
		void StartGame(TSubclassOf<class AA_Gun> SpawnWeaponClass);

	UFUNCTION()
		void OpenMenu(UUserWidget* CurrentMenu, MenuType MenuToOpen);

	UFUNCTION()
		void QuitGame();

	APlayerController* PlayerController;

	UGI_Incursion* GameInstance;

	// Main Menu
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_MainMenu> WidgetMainMenuClass;
	// Widget Instance
	UPROPERTY()
		class UW_MainMenu* WidgetMainMenu;

	// Weapon Select Menu
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_WeaponSelect> WidgetWeaponSelectClass;
	UPROPERTY()
		class UW_WeaponSelect* WidgetWeaponSelect;

	// Controls Menu
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_Controls> WidgetControlsClass;
	// Widget Instance
	UPROPERTY()
		class UW_Controls* WidgetControls;

	// Credits Menu
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_Credits> WidgetCreditsClass;
	// Widget Instance
	UPROPERTY()
		class UW_Credits* WidgetCredits;

	UPROPERTY(EditAnywhere)
		TArray<UUserWidget*> WidgetMenus;
};
