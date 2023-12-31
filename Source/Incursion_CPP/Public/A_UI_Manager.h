
#pragma once

#include "CoreMinimal.h"

#include "A_Tower.h"
#include "BFL_Incursion.h"
#include "GameFramework/Actor.h"
#include "PC_PlayerController.h"
#include "W_Controls.h"
#include "W_HUD.h"
#include "W_LoseScreen.h"
#include "W_Options.h"
#include "W_PauseMenu.h"
#include "W_Store.h"
#include "W_WinScreen.h"

#include "A_UI_Manager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIManager_RequestTogglePauseGame, bool, PauseGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUIManager_RequestRestartGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUIManager_RequestMainMenu);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIManager_RequestCheckCanPurchaseTower, TSubclassOf<class AA_Tower>, TowerClass);

UCLASS()
class INCURSION_CPP_API AA_UI_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	AA_UI_Manager();

	void Initialise(APC_PlayerController* PlayerControllerRef);
	void ToggleMenu(UW_Widget* Widget);
	void DisplayCantBuildWidget();
	void ShowLoseScreen();
	void ShowWinScreen();

	UPROPERTY()
		UW_HUD* WidgetHUD;

	FUIManager_RequestTogglePauseGame RequestTogglePauseGame;
	FUIManager_RequestRestartGame RequestRestartGame;
	FUIManager_RequestMainMenu RequestMainMenu;
	FUIManager_RequestCheckCanPurchaseTower RequestCheckCanPurchaseTower;

	UW_Options* WidgetOptionsMenu;
	UW_PauseMenu* WidgetPauseMenu;
	UW_Store* WidgetStoreMenu;

private:
	TSubclassOf<class UUserWidget> GetWidgetBP_Class(FString WidgetBP_FileName);

	template <typename WidgetStaticClass>
	UW_Widget* SetUpMenu(UW_Widget* Widget, TSubclassOf<class UW_Widget> WidgetClass);
	void HideCantBuildWidget();

	UFUNCTION()
		void OpenMenu(UW_Widget* CurrentMenu, MenuType MenuToOpen);

	UFUNCTION()
		void BroadcastRequestTogglePauseGame(bool Pause);

	UFUNCTION()
		void BroadcastRequestMainMenu();	
	
	UFUNCTION()
		void BroadcastRequestRestartGame();

	UFUNCTION()
		void BroadcastRequestCheckCanPurchaseTower(TSubclassOf<class AA_Tower> TowerClass);

	UBFL_Incursion* BFL_Incursion;
	APC_PlayerController* PlayerController;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD> WidgetHUD_Class;

	TSubclassOf<class UW_PauseMenu> WidgetPauseMenuClass;

	TSubclassOf<class UW_Options> WidgetOptionsMenuClass;
	
	UW_Controls* WidgetControlsMenu;
	TSubclassOf<class UW_Controls> WidgetControlsMenuClass;

	UW_LoseScreen* WidgetLoseMenu;
	TSubclassOf<class UW_LoseScreen> WidgetLoseMenuClass;	
	
	UW_WinScreen* WidgetWinMenu;
	TSubclassOf<class UW_WinScreen> WidgetWinMenuClass;

	TSubclassOf<class UW_Store> WidgetStoreMenuClass;

	FInputModeGameAndUI InputGameAndUI_Parameters;

	FTimerHandle TH_WidgetCantBuild;

	USoundBase* LoseScreenMusic;
	USoundBase* WinScreenMusic;
};
