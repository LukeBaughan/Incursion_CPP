
#include "W_HUD_Lives.h"

void UW_HUD_Lives::Initialise_Implementation()
{
	// OVERRIDE IN BP AND SET TextBlockLives BEFORE PARENT INITIALISE
}

void UW_HUD_Lives::SetLives(int Amount)
{
	FText TextLives = FText::Format(FText::FromString(TEXT("LIVES: {0}")), FText::AsNumber(Amount));
	if (TextBlockLives)
	{
		TextBlockLives->SetText(TextLives);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("W_HUD_Lives: Unable to get TextBlockLives"));
	}
}