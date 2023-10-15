// Fill out your copyright notice in the Description page of Project Settings.


// ToDo: MAKE MENU CREATION CODE MORE OPTIMAL IN THE FUTURE 


#include "GM_MainMenu.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AGM_MainMenu::AGM_MainMenu() :
	GameInstance(nullptr),
	WidgetMainMenu(nullptr),
	WidgetWeaponSelect(nullptr),
	WidgetControls(nullptr),
	WidgetCredits(nullptr)
{
	DefaultPawnClass = NULL;

	// Gets a blueprint of each menu widget to set each class reference
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetMainMenuClassFinder(TEXT("/Game/Luke/UI/MainMenu/W_MainMenuBP"));
	if (WidgetMainMenuClassFinder.Succeeded())
		WidgetMainMenuClass = WidgetMainMenuClassFinder.Class;

	// Weapon Select Menu
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetWeaponSelectClassFinder(TEXT("/Game/Luke/UI/MainMenu/W_WeaponSelectBP"));
	if (WidgetWeaponSelectClassFinder.Succeeded())
		WidgetWeaponSelectClass = WidgetWeaponSelectClassFinder.Class;

	// Controls Menu
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetControlsClassFinder(TEXT("/Game/Luke/UI/MainMenu/W_ControlsBP"));
	if (WidgetControlsClassFinder.Succeeded())
		WidgetControlsClass = WidgetControlsClassFinder.Class;

	// Credits Menu
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetCreditsClassFinder(TEXT("/Game/Luke/UI/MainMenu/W_CreditsBP"));
	if (WidgetCreditsClassFinder.Succeeded())
		WidgetCreditsClass = WidgetCreditsClassFinder.Class;


	// TEST CODE
	/*
	WidgetMenus.Add(WidgetMainMenu);
	WidgetMenus.Add(WidgetWeaponSelect);
	WidgetMenus.Add(WidgetControls);
	WidgetMenus.Add(WidgetCredits);
	*/

}

void AGM_MainMenu::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UGI_Incursion>(GetGameInstance());

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
		else
		{
			UE_LOG(LogTemp, Error, TEXT("GM_MainMenu: WidgetMainMenu Invalid"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GM_MainMenu: WidgetMainMenuClass Invalid"));
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
		else
		{
			UE_LOG(LogTemp, Error, TEXT("GM_MainMenu: WidgetWeaponSelect Invalid"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GM_MainMenu: WidgetWeaponSelectClass Invalid"));
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
		else
		{
			UE_LOG(LogTemp, Error, TEXT("GM_MainMenu: WidgetControls Invalid"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GM_MainMenu: WidgetControlsClass Invalid"));
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
		else
		{
			UE_LOG(LogTemp, Error, TEXT("GM_MainMenu: WidgetCredits Invalid"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GM_MainMenu: WidgetCreditsClass Invalid"));
	}
}

// TEST FUNCTION (Havent tested in UE5; created with GitHub IOS app)
/*
void AGM_MainMenu::SetUpMenusTest()
{

	// Iterates through each menu widget and set them up
	for (UUserWidget* WidgetMenu : WidgetMenus)
	{
		if (WidgetMenu != nullptr)
		{
			WidgetMenu = CreateWidget<UUserWidget>(PlayerController, WidgetMenu->GetClass());
			// If the created menu is valid, initialise it and and it to the players viewport
			if (WidgetMenu)
			{
				//WidgetMenu->init
				WidgetMenu->AddToViewport();

				WidgetMenu->BackButton->ButtonOnRequesOpenMenu.AddDynamic(this, &UGM_MainMenu::OpenMenu);
				if (WidgetMenu->QuitButton)
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
	if (MenuToOpenRef)
	{
		UBFL_Incursion::OpenMenu(CurrentMenu, MenuToOpenRef);
	}
}

void AGM_MainMenu::StartGame(TSubclassOf<AA_Gun> SpawnWeaponClass)
{
	// Sets the spawn weapon in the game instance so that GM_Incursion can access it
	GameInstance->SetSpawnWeaponClass(SpawnWeaponClass);

	UGameplayStatics::OpenLevel(GetWorld(), FName("Level_1"), true);
}

void AGM_MainMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
}