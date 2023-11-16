
#include "A_UI_Manager.h"
#include "Kismet/GameplayStatics.h"

AA_UI_Manager::AA_UI_Manager() :
	PlayerController(nullptr),
	WidgetHUD(nullptr),
	WidgetHUD_Class(NULL),

	WidgetPauseMenu(nullptr),
	WidgetPauseMenuClass(NULL),

	WidgetControlsMenu(nullptr),
	WidgetControlsMenuClass(NULL),

	WidgetStoreMenu(nullptr),
	WidgetStoreMenuClass(NULL)
{
	WidgetHUD_Class = GetWidgetBP_Class(TEXT("HUD/W_HUD_BP"));
	WidgetPauseMenuClass = GetWidgetBP_Class(TEXT("W_PauseMenu_BP"));
	WidgetControlsMenuClass = GetWidgetBP_Class(TEXT("MainMenu/W_ControlsBP"));
	WidgetStoreMenuClass = GetWidgetBP_Class(TEXT("W_Store_BP"));
	

	InputGameAndUI_Parameters.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
	InputGameAndUI_Parameters.SetHideCursorDuringCapture(true);
}

TSubclassOf<class UUserWidget> AA_UI_Manager::GetWidgetBP_Class(FString WidgetBP_FileName)
{
	FString WidgetFilePath = TEXT("/Game/Luke/UI/") + WidgetBP_FileName;

	ConstructorHelpers::FClassFinder<class UUserWidget> WidgetCF(*WidgetFilePath);
	if (WidgetCF.Succeeded())
	{
		return WidgetCF.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, (TEXT("A_UI_Manager: Unable to get Widget Class")));
		return NULL;
	}
}

void AA_UI_Manager::Initialise(APC_PlayerController* PlayerControllerRef)
{
	PlayerController = PlayerControllerRef;

	WidgetHUD = Cast<UW_HUD>(SetUpMenu<UW_HUD>(WidgetHUD, WidgetHUD_Class));

	WidgetPauseMenu = Cast<UW_PauseMenu>(SetUpMenu<UW_PauseMenu>(WidgetPauseMenu, WidgetPauseMenuClass));
	WidgetPauseMenu->OnRequestOpenMenu.AddDynamic(this, &AA_UI_Manager::OpenMenu);
	WidgetPauseMenu->RequestTogglePause.AddDynamic(this, &AA_UI_Manager::BroadcastRequestTogglePauseGame);
	WidgetPauseMenu->RequestMainMenu.AddDynamic(this, &AA_UI_Manager::BroadcastRequestMainMenu);

	WidgetControlsMenu = Cast<UW_Controls>(SetUpMenu<UW_Controls>(WidgetControlsMenu, WidgetControlsMenuClass));
	WidgetControlsMenu->BackButton->ButtonOnRequestOpenMenu.AddDynamic(this, &AA_UI_Manager::OpenMenu);

	WidgetStoreMenu = Cast<UW_Store>(SetUpMenu<UW_Store>(WidgetStoreMenu, WidgetStoreMenuClass));
	WidgetStoreMenu->OnRequestTower.AddDynamic(this, &AA_UI_Manager::BroadcastRequestCheckCanPurchaseTower);
}

template <typename WidgetStaticClass>
UW_Widget* AA_UI_Manager::SetUpMenu(UW_Widget* Widget, TSubclassOf<class UW_Widget> WidgetClass)
{
	if (WidgetClass)
	{
		Widget = CreateWidget<WidgetStaticClass>(PlayerController, WidgetClass);
		if (Widget)
		{
			Widget->Initialise();
			Widget->AddToViewport();
			return Widget;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("GM_MainMenu: Widget Invalid"));
			return nullptr;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GM_MainMenu: WidgetClass Invalid"));
		return nullptr;
	}
}

// Shows/ Hides the specified menu widget and enables/ disables mouse input
void AA_UI_Manager::ToggleMenu(UW_Widget* Widget)
{
	switch (Widget->GetVisibility())
	{
	case ESlateVisibility::Visible:
		Widget->SetVisibility(ESlateVisibility::Collapsed);
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
		WidgetHUD->SetVisibility(ESlateVisibility::Visible);
		break;
	case ESlateVisibility::Collapsed:
		Widget->SetVisibility(ESlateVisibility::Visible);
		PlayerController->SetInputMode(InputGameAndUI_Parameters);
		PlayerController->SetShowMouseCursor(true);
		WidgetHUD->SetVisibility(ESlateVisibility::Collapsed);
		// Hides the store menu if the pause menu is opened
		if (Widget == WidgetPauseMenu)
		{
			WidgetStoreMenu->SetVisibility(ESlateVisibility::Collapsed);
		}
		break;
	}
}

// Called when the player tries placing the tower in an invalid place
void AA_UI_Manager::DisplayCantBuildWidget()
{
	WidgetHUD->WidgetCantBuild->SetVisibility(ESlateVisibility::Visible);

	GetWorldTimerManager().SetTimer(TH_WidgetCantBuild, this, &AA_UI_Manager::HideCantBuildWidget, 1.0f, false);
}

void AA_UI_Manager::HideCantBuildWidget()
{
	WidgetHUD->WidgetCantBuild->SetVisibility(ESlateVisibility::Collapsed);
	GetWorldTimerManager().ClearTimer(TH_WidgetCantBuild);
}

// Closes the passed menu and opens the selected menu
void AA_UI_Manager::OpenMenu(UW_Widget* CurrentMenu, MenuType MenuToOpen)
{
	switch (MenuToOpen)
	{
	case Main:
		BFL_Incursion->OpenMenu(CurrentMenu, WidgetPauseMenu);
		break;
	case Options:
		break;
	case Controls:
		BFL_Incursion->OpenMenu(CurrentMenu, WidgetControlsMenu);
		break;
	case Win:
		break;
	case Lose:
		break;
	}
}

void AA_UI_Manager::BroadcastRequestTogglePauseGame(bool Pause)
{
	RequestTogglePauseGame.Broadcast(Pause);
}

void AA_UI_Manager::BroadcastRequestMainMenu()
{
	RequestMainMenu.Broadcast();
}

void AA_UI_Manager::BroadcastRequestCheckCanPurchaseTower(TSubclassOf<class AA_Tower> TowerClass)
{
	RequestCheckCanPurchaseTower.Broadcast(TowerClass);
}