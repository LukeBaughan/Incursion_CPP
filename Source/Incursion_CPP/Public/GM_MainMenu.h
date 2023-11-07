
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

	TSubclassOf<class UUserWidget> GetWidgetBP_Class(FString WidgetBP_FileName);

	UFUNCTION()
		void StartGame(TSubclassOf<class AA_Gun> SpawnWeaponClass);

	UFUNCTION()
		void OpenMenu(UW_Widget* CurrentMenu, MenuType MenuToOpen);

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
