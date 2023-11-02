// Fill out your copyright notice in the Description page of Project Settings.


#include "W_HUD.h"

void UW_HUD::Initialise_Implementation()
{
	// OVERRIDE IN BP AND SET WIDGETS BEFORE PARENT INITIALISE

	if (WidgetLives)
	{
		WidgetLives->Initialise();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UW_HUD: WidgetLives Invalid"));
	}

	if (WidgetAmmo)
	{
		WidgetAmmo->Initialise();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UW_HUD: WidgetAmmo Invalid"));
	}

	if (WidgetTimer)
	{
		WidgetTimer->Initialise();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UW_HUD: WidgetTimer Invalid"));
	}

	if (WidgetSkipCountdown)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UW_HUD: WidgetSkipCountdown Invalid"));
	}
}