// Fill out your copyright notice in the Description page of Project Settings.


#include "W_HUD_Ammo.h"

void UW_HUD_Ammo::Initialise_Implementation()
{
	// OVERRIDE IN BP AND SET TextBlockAmmo BEFORE PARENT INITIALISE
}

void UW_HUD_Ammo::SetAmmoAmount(int8 MaxAmmo, int8 CurrentAmmo)
{
	FText AmmoText = FText::Format(FText::FromString(TEXT("{0} / {1}")), FText::AsNumber(CurrentAmmo), FText::AsNumber(MaxAmmo));
	if(TextBlockAmmo)
	{
		TextBlockAmmo->SetText(AmmoText);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("W_HUD_Ammo: Unable to get TextBlockAmmo"));
	}
}