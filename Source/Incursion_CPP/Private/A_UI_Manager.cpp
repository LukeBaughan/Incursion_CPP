// Fill out your copyright notice in the Description page of Project Settings.


#include "A_UI_Manager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AA_UI_Manager::AA_UI_Manager() :
	PlayerController(nullptr),
	WidgetHUD(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// HUD
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetHUD_ClassFinder(TEXT("/Game/Luke/UI/HUD/W_HUD_BP"));
	if (WidgetHUD_ClassFinder.Succeeded())
		WidgetHUD_Class = WidgetHUD_ClassFinder.Class;
}

// Called when the game starts or when spawned
void AA_UI_Manager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AA_UI_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AA_UI_Manager::Initialise(APC_PlayerController* PlayerControllerRef)
{
	PlayerController = PlayerControllerRef;

	// HUD
	// If the widget class is valid
	if (WidgetHUD_Class != nullptr)
	{
		WidgetHUD = CreateWidget<UW_HUD>(PlayerController, WidgetHUD_Class);
		// If the created widget is valid, initialise it and add it to the viewport
		if (WidgetHUD)
		{ 
			WidgetHUD->Initialise();
			WidgetHUD->AddToViewport();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("A_UI_Manager: WidgetHUD Invalid"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("A_UI_Manager: WidgetHUD_Class Invalid"));
	}
}