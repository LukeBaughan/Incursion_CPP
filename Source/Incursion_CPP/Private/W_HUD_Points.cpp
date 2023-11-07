
#include "W_HUD_Points.h"

void UW_HUD_Points::Initialise_Implementation()
{
	// OVERRIDE IN BP AND SET TextBlockLives BEFORE PARENT INITIALISE
}

void UW_HUD_Points::SetPoints(int Points)
{
	FText TextPoints = FText::Format(FText::FromString(TEXT("POINTS: {0}")), FText::AsNumber(Points));
	if(TextBlockPoints)
	{
		TextBlockPoints->SetText(TextPoints);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("W_HUD_Points: Unable to get TextBlockPoints"));
	}
}