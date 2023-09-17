// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_MainMenu.h"
#include "Blueprint/UserWidget.h"
#include "W_MainMenu.h"
#include "Kismet/GameplayStatics.h"

AGM_MainMenu::AGM_MainMenu()
{
	// Gets a blueprint main menu widget class reference
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/Luke/UI/W_MainMenuBP"));
	if (WidgetClassFinder.Succeeded())
		WidgetMainMenuClass = (WidgetClassFinder.Class);
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
	// If the widget clas is valid, create a new widget of that class and add it to the viewport
	if (WidgetMainMenuClass != nullptr)
	{
		WidgetMainMenu = CreateWidget<UW_MainMenu>(PlayerController, WidgetMainMenuClass);
		if (WidgetMainMenu)
			WidgetMainMenu->AddToViewport();
	}

	PlayerController->bShowMouseCursor = true;
}