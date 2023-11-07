
#pragma once

#include "CoreMinimal.h"

#include "BFL_Incursion.h"
#include "GameFramework/Actor.h"
#include "PC_PlayerController.h"
#include "W_Controls.h"
#include "W_HUD.h"
#include "W_PauseMenu.h"

#include "A_UI_Manager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIManager_RequestTogglePauseGame, bool, PauseGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUIManager_RequestMainMenu);

UCLASS()
class INCURSION_CPP_API AA_UI_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	AA_UI_Manager();

	void Initialise(APC_PlayerController* PlayerControllerRef);
	void ToggleMenu(UW_Widget* Widget);

	UPROPERTY()
		UW_HUD* WidgetHUD;

	FUIManager_RequestTogglePauseGame RequestTogglePauseGame;
	FUIManager_RequestMainMenu RequestMainMenu;

	UW_PauseMenu* WidgetPauseMenu;

private:
	TSubclassOf<class UUserWidget> GetWidgetBP_Class(FString WidgetBP_FileName);

	template <typename WidgetStaticClass>
	UW_Widget* SetUpMenu(UW_Widget* Widget, TSubclassOf<class UW_Widget> WidgetClass);

	UFUNCTION()
		void OpenMenu(UW_Widget* CurrentMenu, MenuType MenuToOpen);

	UFUNCTION()
		void BroadcastRequestTogglePauseGame(bool Pause);

	UFUNCTION()
		void BroadcastRequestMainMenu();

	UBFL_Incursion* BFL_Incursion;
	APC_PlayerController* PlayerController;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD> WidgetHUD_Class;

	TSubclassOf<class UW_PauseMenu> WidgetPauseMenuClass;

	UW_Controls* WidgetControlsMenu;
	TSubclassOf<class UW_Controls> WidgetControlsMenuClass;

	FInputModeGameAndUI InputGameAndUI_Parameters;
};
