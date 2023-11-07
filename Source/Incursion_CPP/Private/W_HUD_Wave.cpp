
#include "W_HUD_Wave.h"

void UW_HUD_Wave::Initialise_Implementation()
{
	// OVERRIDE IN BP AND SET TextBlockWave BEFORE PARENT INITIALISE
}

void UW_HUD_Wave::SetWave(uint8 CurrentWave, uint8 MaxWaves)
{
	FText TextWave = FText::Format(FText::FromString(TEXT("WAVE: {0} / {1}")), FText::AsNumber(CurrentWave), FText::AsNumber(MaxWaves));
	if (TextBlockWave)
	{
		TextBlockWave->SetText(TextWave);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("W_HUD_Wave: Unable to get TextBlockWave"));
	}
}
