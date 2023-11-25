
#include "W_Stats.h"

void UW_Stats::Initialise_Implementation()
{
	BackButton->Initialise();
	BackButton->SetButtonParent(this);
}

void UW_Stats::SetDeaths(int Amount)
{
	SetStatsTextBlock(TextBlockDeaths, Amount);
}

void UW_Stats::SetEnemiesKilled(int Amount)
{
	SetStatsTextBlock(TextBlockEnemiesKilled, Amount);
}

void UW_Stats::SetGamesPlayed(int Amount)
{
	SetStatsTextBlock(TextBlockGamesPlayed, Amount);
}

void UW_Stats::SetGamesWon(int Amount)
{
	SetStatsTextBlock(TextBlockGamesWon, Amount);
}

void UW_Stats::SetTotalPoints(int Amount)
{
	SetStatsTextBlock(TextBlockTotalPoints, Amount);
}

void UW_Stats::SetStatsTextBlock(UTextBlock* TextBlock, int Amount)
{
	FText Text = FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(Amount));
	if (TextBlock)
	{
		TextBlock->SetText(Text);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UW_Stats: Unable to get TextBlock"));
	}
}
