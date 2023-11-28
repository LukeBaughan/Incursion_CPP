
#pragma once

#include "CoreMinimal.h"

#include "A_SettingsManager.h"
#include "A_StatsManager.h"
#include "BFL_Incursion.h"
#include "GameFramework/GameModeBase.h"
#include "GI_Incursion.h"
#include "P_PlayerCamera.h"
#include "W_Controls.h"
#include "W_Credits.h"
#include "W_MainMenu.h"
#include "W_Options.h"
#include "W_Stats.h"
#include "W_WeaponSelect.h"
#include "W_Widget.h"

#include "GM_MainMenu.generated.h"

UCLASS()
class INCURSION_CPP_API AGM_MainMenu : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGM_MainMenu();

private:
	virtual void BeginPlay();

	template <typename WidgetStaticClass>
	UW_Widget* SetUpMenu(UW_Widget* Widget, TSubclassOf<class UW_Widget> WidgetClass);

	TSubclassOf<class UUserWidget> GetWidgetBP_Class(FString WidgetBP_FileName, FString WidgetBP_FileNameBase = "/Game/Luke/UI/MainMenu/");

	UFUNCTION()
		void StartGame(TSubclassOf<class AA_Gun> SpawnWeaponClass);

	UFUNCTION()
		void OpenMenu(UW_Widget* CurrentMenu, MenuType MenuToOpen);

	UFUNCTION()
		void QuitGame();

	UGI_Incursion* GameInstance;
	AA_SettingsManager* SettingsManager;
	AA_StatsManager* StatsManager;

	APlayerController* PlayerController;

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

	// Options Menu
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_Options> WidgetOptionsClass;
	// Widget Instance
	UPROPERTY()
		class UW_Options* WidgetOptions;

	// Stats Menu
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_Stats> WidgetStatsClass;
	// Widget Instance
	UPROPERTY()
		class UW_Stats* WidgetStats;

	UPROPERTY(EditAnywhere)
		TArray<UUserWidget*> WidgetMenus;
};
