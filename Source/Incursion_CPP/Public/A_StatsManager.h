
#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "SG_Incursion.h"

#include "A_StatsManager.generated.h"

UCLASS()
class INCURSION_CPP_API AA_StatsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AA_StatsManager();

	void Initialise();
	void IncrementGamesPlayed();
	void IncrementGamesWon();

	UFUNCTION()
		void IncrementEnemiesKilled();

	UFUNCTION()
		void IncrementPlayerDeaths();

	UFUNCTION()
		void IncreaseTotalPoints(int Amount);

	UPROPERTY()
		USG_Incursion* SaveGameInstance;

private:
	FString SaveFileName;
};
