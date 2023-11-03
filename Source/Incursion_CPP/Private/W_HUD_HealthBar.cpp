
#include "W_HUD_HealthBar.h"

#include "BFL_Incursion.h"

void UW_HUD_HealthBar::Initialise_Implementation()
{
	// OVERRIDE IN BP AND SET HealthBar BEFORE PARENT INITIALISE
}

void UW_HUD_HealthBar::SetHealthBarAmount(float CurrentHealth, float MaxHealth)
{
	if (HealthBar)
	{
		BFL_Incursion->SetHealthBarAmount(HealthBar, CurrentHealth, MaxHealth);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("W_HUD_HealthBar: Unable to get HealthBar"));
	}
}