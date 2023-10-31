// Fill out your copyright notice in the Description page of Project Settings.


#include "W_HUD.h"

void UW_HUD::Initialise_Implementation()
{
	// OVERRIDE IN BP AND SET WIDGETS BEFORE PARENT INITIALISE

	//Lives
	if (WidgetLives)
	{
		WidgetLives->Initialise();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UW_HUD: WidgetLives Invalid"));
	}

	// Ammo
	if (WidgetAmmo)
	{
		WidgetAmmo->Initialise();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UW_HUD: WidgetAmmo Invalid"));
	}
}