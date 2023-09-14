// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_MainMenu.h"
#include "Kismet/GameplayStatics.h"

void AGM_MainMenu::BeginPlay()
{
	// Sets the player controller to the in-game player controller 
	// index = 0 to get the first player controller (theres only one since its single-player)
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// Gets the player camera and sets the player controller to posses it
	TArray<AActor*> PlayerCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AP_PlayerCamera::StaticClass(), PlayerCameras);
	PlayerController->Possess(Cast<APawn>(PlayerCameras[0])); // Theres only one player camera

}