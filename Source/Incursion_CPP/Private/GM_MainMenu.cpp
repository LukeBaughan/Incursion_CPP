
#include "GM_MainMenu.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AGM_MainMenu::AGM_MainMenu() :
	StatsManager(nullptr),
	GameInstance(nullptr),
	WidgetMainMenu(nullptr),
	WidgetWeaponSelect(nullptr),
	WidgetControls(nullptr),
	WidgetCredits(nullptr),
	WidgetOptions(nullptr),
	WidgetStats(nullptr)
{
	DefaultPawnClass = NULL;

	// Gets a blueprint of each menu widget to set each class reference
	WidgetMainMenuClass = GetWidgetBP_Class(TEXT("W_MainMenuBP"));
	WidgetWeaponSelectClass = GetWidgetBP_Class(TEXT("W_WeaponSelectBP"));
	WidgetControlsClass = GetWidgetBP_Class(TEXT("W_ControlsBP"));
	WidgetCreditsClass = GetWidgetBP_Class(TEXT("W_CreditsBP"));
	WidgetOptionsClass = GetWidgetBP_Class(TEXT("W_Options_BP"), TEXT("/Game/Luke/UI/"));
	WidgetStatsClass = GetWidgetBP_Class(TEXT("W_Stats_BP"));
}

TSubclassOf<class UUserWidget> AGM_MainMenu::GetWidgetBP_Class(FString WidgetBP_FileName, FString WidgetBP_FileNameBase)
{
	FString WidgetFilePath = WidgetBP_FileNameBase + WidgetBP_FileName;

	ConstructorHelpers::FClassFinder<class UUserWidget> WidgetCF(*WidgetFilePath);
	if (WidgetCF.Succeeded())
	{
		return WidgetCF.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, (TEXT("GM_MainMenu: Unable to get Widget Class")));
		return NULL;
	}
}

void AGM_MainMenu::BeginPlay()
{
	Super::BeginPlay();

	StatsManager = GetWorld()->SpawnActor<AA_StatsManager>(AA_StatsManager::StaticClass());
	StatsManager->Initialise();

	GameInstance = Cast<UGI_Incursion>(GetGameInstance());

	// Sets the player controller to the in-game player controller 
	// index = 0 to get the first player controller (theres only one since its single-player)
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// Gets the player camera and sets the player controller to posses it
	TArray<AActor*> PlayerCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AP_PlayerCamera::StaticClass(), PlayerCameras);
	PlayerController->Possess(Cast<APawn>(PlayerCameras[0])); // Theres only one player camera

	PlayerController->bShowMouseCursor = true;

	WidgetMainMenu = Cast<UW_MainMenu>(SetUpMenu<UW_MainMenu>(WidgetMainMenu, WidgetMainMenuClass));
	WidgetMainMenu->OnRequestQuitGame.AddDynamic(this, &AGM_MainMenu::QuitGame);
	WidgetMainMenu->OnRequestOpenMenu.AddDynamic(this, &AGM_MainMenu::OpenMenu);

	WidgetWeaponSelect = Cast<UW_WeaponSelect>(SetUpMenu<UW_WeaponSelect>(WidgetWeaponSelect, WidgetWeaponSelectClass));
	WidgetWeaponSelect->OnWeaponSelected.AddDynamic(this, &AGM_MainMenu::StartGame);
	WidgetWeaponSelect->BackButton->ButtonOnRequestOpenMenu.AddDynamic(this, &AGM_MainMenu::OpenMenu);

	WidgetControls = Cast<UW_Controls>(SetUpMenu<UW_Controls>(WidgetControls, WidgetControlsClass));
	WidgetControls->BackButton->ButtonOnRequestOpenMenu.AddDynamic(this, &AGM_MainMenu::OpenMenu);

	WidgetCredits = Cast<UW_Credits>(SetUpMenu<UW_Credits>(WidgetCredits, WidgetCreditsClass));
	WidgetCredits->BackButton->ButtonOnRequestOpenMenu.AddDynamic(this, &AGM_MainMenu::OpenMenu);

	WidgetOptions = Cast<UW_Options>(SetUpMenu<UW_Options>(WidgetOptions, WidgetOptionsClass));
	WidgetOptions->BackButton->ButtonOnRequestOpenMenu.AddDynamic(this, &AGM_MainMenu::OpenMenu);	
	
	WidgetStats = Cast<UW_Stats>(SetUpMenu<UW_Stats>(WidgetStats, WidgetStatsClass));
	WidgetStats->BackButton->ButtonOnRequestOpenMenu.AddDynamic(this, &AGM_MainMenu::OpenMenu);	
	WidgetStats->SetDeaths(StatsManager->SaveGameInstance->PlayerDeaths);
	WidgetStats->SetEnemiesKilled(StatsManager->SaveGameInstance->EnemiesKilled);
	WidgetStats->SetGamesPlayed(StatsManager->SaveGameInstance->GamesPlayed);
	WidgetStats->SetGamesWon(StatsManager->SaveGameInstance->GamesWon);
	WidgetStats->SetTotalPoints(StatsManager->SaveGameInstance->TotalPoints);
}

template <typename WidgetStaticClass> 
UW_Widget* AGM_MainMenu::SetUpMenu(UW_Widget* Widget, TSubclassOf<class UW_Widget> WidgetClass)
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

// Closes the current menu and opens the selected menu
void AGM_MainMenu::OpenMenu(UW_Widget* CurrentMenu, MenuType MenuToOpen)
{
	UW_Widget* MenuToOpenRef = nullptr;

	switch (MenuToOpen)
	{
	case Main:
		MenuToOpenRef = WidgetMainMenu;
		break;
	case Credits:
		MenuToOpenRef = WidgetCredits;
		break;
	case Options:
		MenuToOpenRef = WidgetOptions;
		break;
	case WeaponSelect:
		MenuToOpenRef = WidgetWeaponSelect;
		break;
	case Statistics:
		MenuToOpenRef = WidgetStats;
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

	UGameplayStatics::OpenLevel(GetWorld(), FName("Level_2"), true);
}

void AGM_MainMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
}