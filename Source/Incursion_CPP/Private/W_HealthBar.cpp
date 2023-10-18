 //Fill out your copyright notice in the Description page of Project Settings.

#include "W_HealthBar.h"

void UW_HealthBar::InitialiseWidget_Implementation()
{
	BFL_Incursion = NewObject<UBFL_Incursion>();
}

void UW_HealthBar::SetHealth(float CurrentHealth, float MaxHealth)
{
	BFL_Incursion->SetHealthBarAmount(ProgressBarHealth, CurrentHealth, MaxHealth);
}