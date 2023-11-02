
#include "W_HUD_Timer.h"

void UW_HUD_Timer::Initialise_Implementation()
{
	// OVERRIDE IN BP AND SET TextBlockCountdownTime BEFORE PARENT INITIALISE
}

void UW_HUD_Timer::SetCountdownTime(int Time)
{
	FText TextCountdownTime = FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(Time));
	if (TextBlockCountdownTime)
	{
		TextBlockCountdownTime->SetText(TextCountdownTime);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("W_HUD_Timer: Unable to get TextBlockCountdownTime"));
	}
}