// Fill out your copyright notice in the Description page of Project Settings.


#include "W_HUD.h"

void UW_HUD::Initialise_Implementation()
{
	// OVERRIDE IN BP AND SET WIDGETS BEFORE PARENT INITIALISE
	Super::Initialise_Implementation();

	for(UW_Widget* Widget : AllWidgets)
	{
		if (Widget)
		{
			Widget->Initialise();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("W_HUD: Widget Invalid"));
		}
	}
}