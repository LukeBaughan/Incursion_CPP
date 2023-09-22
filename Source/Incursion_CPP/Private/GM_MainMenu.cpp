// Fill out your copyright notice in the Description page of Project Settings.


// ToDo: MAKE MENU CREATION CODE MORE OPTIMAL IN THE FUTURE 


#include "GM_MainMenu.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AGM_MainMenu::AGM_MainMenu()
{
	// Gets a blueprint of each menu widget to set each class reference
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetMainMenuClassFinder(TEXT("/Game/Luke/UI/W_MainMenuBP"));
	if (WidgetMainMenuClassFinder.Succeeded())
		WidgetMainMenuClass = WidgetMainMenuClassFinder.Class;
	
	WidgetMainMenu = nullptr;

	// Weapon Select Menu
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetWeaponSelectClassFinder(TEXT("/Game/Luke/UI/W_WeaponSelectBP"));
	if (WidgetWeaponSelectClassFinder.Succeeded())
		WidgetWeaponSelectClass = WidgetWeaponSelectClassFinder.Class;

	WidgetWeaponSelect = nullptr;

	// Controls Menu
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetControlsClassFinder(TEXT("/Game/Luke/UI/W_ControlsBP"));
	if (WidgetControlsClassFinder.Succeeded())
		WidgetControlsClass = WidgetControlsClassFinder.Class;

	WidgetControls = nullptr;

	// Credits Menu
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetCreditsClassFinder(TEXT("/Game/Luke/UI/W_CreditsBP"));
	if (WidgetCreditsClassFinder.Succeeded())
		WidgetCreditsClass = WidgetCreditsClassFinder.Class;

	WidgetCredits = nullptr;

// TEST CODE
/*
	WidgetMenus.Add(WidgetMainMenu);
	WidgetMenus.Add(WidgetWeappnSelect);
	WidgetMenus.Add(Controls);
 WidgetMenus.Add(Credits);
*/
}

void AGM_MainMenu::BeginPlay()
{
	Super::BeginPlay();

	// Sets the player controller to the in-game player controller 
	// index = 0 to get the first player controller (theres only one since its single-player)
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// Gets the player camera and sets the player controller to posses it
	TArray<AActor*> PlayerCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AP_PlayerCamera::StaticClass(), PlayerCameras);
	PlayerController->Possess(Cast<APawn>(PlayerCameras[0])); // Theres only one player camera

	SetUpMenus();

}

void AGM_MainMenu::SetUpMenus()
{
	// Main Menu
	// If the widget class is valid
	if (WidgetMainMenuClass != nullptr)
	{
		WidgetMainMenu = CreateWidget<UW_MainMenu>(PlayerController, WidgetMainMenuClass);
		// If the created widget is valid, initialise it and add it to the viewport
		if (WidgetMainMenu)
		{
			WidgetMainMenu->Initialise();
			WidgetMainMenu->AddToViewport();

			// Bind Event to when the quit button is pressed in the main menu
			WidgetMainMenu->OnRequestQuitGame.AddDynamic(this, &AGM_MainMenu::QuitGame);
			// Bind Event to when any button which opens a menu is pressed in the main menu
			WidgetMainMenu->OnRequestOpenMenu.AddDynamic(this, &AGM_MainMenu::OpenMenu);
		}
	}

	PlayerController->bShowMouseCursor = true;

	// Weapon Select
	if (WidgetWeaponSelectClass != nullptr)
	{
		WidgetWeaponSelect = CreateWidget<UW_WeaponSelect>(PlayerController, WidgetWeaponSelectClass);
		if (WidgetWeaponSelect)
		{
			WidgetWeaponSelect->Initialise();
			WidgetWeaponSelect->AddToViewport();

			// Opens the level when a weapon is selected
			WidgetWeaponSelect->OnWeaponSelected.AddDynamic(this, &AGM_MainMenu::StartGame);
			// Set Up Back Button Delegate
			WidgetWeaponSelect->BackButton->ButtonOnRequestOpenMenu.AddDynamic(this, &AGM_MainMenu::OpenMenu);
		}
	}
	
	// Controls
	if (WidgetControlsClass != nullptr)
	{
		WidgetControls = CreateWidget<UW_Controls>(PlayerController, WidgetControlsClass);
		if (WidgetControls)
		{
			WidgetControls->Initialise();
			WidgetControls->AddToViewport();

			// Set Up Back Button Delegate
			WidgetControls->BackButton->ButtonOnRequestOpenMenu.AddDynamic(this, &AGM_MainMenu::OpenMenu);
		}
	}

	// Credits Menu
	if (WidgetCreditsClass != nullptr)
	{
		WidgetCredits = CreateWidget<UW_Credits>(PlayerController, WidgetCreditsClass);
		if (WidgetCredits)
		{
			WidgetCredits->Initialise();
			WidgetCredits->AddToViewport();

			// Set Up Back Button Delegate
			WidgetCredits->BackButton->ButtonOnRequestOpenMenu.AddDynamic(this, &AGM_MainMenu::OpenMenu);
		}
	}
}

// TEST FUNCTION (Havent tested in UE5; created with GitHub IOS app)
/*
void AGM_MainMenu::SetUpMenusTest()
{

// Iterates through each menu widget and set them up
	for(UUserWidget* WidgetMenu : WidgetMenus)
	{
		if(WidgetMenu != nullptr)
		{
			WidgetMenu = CreateMenu<WidgetMenu.Class>(PlayerControler, WidgetMenu.Class);
// If the created menu is valid, initialise it and and it to the players viewport
			if(WidgetMenu)
			{
				WidgetMenu.Initialise();
				WidgetMenu.AddToViewport();

				WidgetMenu->BackButton->ButtonOnRequesOpenMenu.AddDynamic(this, &UGM_MainMenu::OpenMenu);
				if(WidgetMenu->QuitButton)
					WidgetMenu->QuitButton->OnRequestQuitGame.AddDynamic(this, &AGM_MainMenu::QuitGame);
			}
		}
	}
}
*/

// Closes the current menu and opens the selected menu
void AGM_MainMenu::OpenMenu(UUserWidget* CurrentMenu, MenuType MenuToOpen)
{
	UUserWidget* MenuToOpenRef = nullptr;

	switch (MenuToOpen)
	{
	case Main:
		MenuToOpenRef = WidgetMainMenu;
		break;
	case Credits:
		MenuToOpenRef = WidgetCredits;
		break;
	case Options:
		break;
	case WeaponSelect:
		MenuToOpenRef = WidgetWeaponSelect;
		break;
	case Statistics:
		break;
	case Controls:
		MenuToOpenRef = WidgetControls;
		break;
	}

	// After getting the menu ref, set its widget to visible
	if(MenuToOpenRef)
		UBFL_Incursion::OpenMenu(CurrentMenu, MenuToOpenRef);
}

void AGM_MainMenu::StartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Level_1"), true);
}

void AGM_MainMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
}