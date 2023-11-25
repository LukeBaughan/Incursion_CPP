
#pragma once

#include "CoreMinimal.h"

#include "Components/TextBlock.h"
#include "W_BackButton.h"
#include "W_Widget.h"

#include "W_Stats.generated.h"

UCLASS()
class INCURSION_CPP_API UW_Stats : public UW_Widget
{
	GENERATED_BODY()

public:
	virtual void Initialise_Implementation() override;

	void SetDeaths(int Amount);
	void SetEnemiesKilled(int Amount);
	void SetGamesPlayed(int Amount);
	void SetGamesWon(int Amount);
	void SetTotalPoints(int Amount);


	UPROPERTY(BlueprintReadWrite)
		UTextBlock* TextBlockDeaths;	
	
	UPROPERTY(BlueprintReadWrite)
		UTextBlock* TextBlockEnemiesKilled;	
	
	UPROPERTY(BlueprintReadWrite)
		UTextBlock* TextBlockGamesPlayed;	
	
	UPROPERTY(BlueprintReadWrite)
		UTextBlock* TextBlockGamesWon;

	UPROPERTY(BlueprintReadWrite)
		UTextBlock* TextBlockTotalPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		UW_BackButton* BackButton;

private:
	void SetStatsTextBlock(UTextBlock* TextBlock, int Amount);

};
