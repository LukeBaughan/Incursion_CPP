
#include "W_Store.h"

#include "Kismet/GameplayStatics.h"

void UW_Store::Initialise_Implementation()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UW_Store::PlayButtonDenySound()
{
	if(ButtonDenySound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonDenySound);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UW_Store::PlayButtonDenySound: Unable to get ButtonDenySound"));
	}
}

void UW_Store::SetTextPlayerPoints(int Points)
{
	FText PointsText = FText::Format(FText::FromString(TEXT("POINTS: {0}")), FText::AsNumber(Points));
	TextPlayerPoints->SetText(PointsText);
}
