
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SG_Incursion.generated.h"

UCLASS()
class INCURSION_CPP_API USG_Incursion : public USaveGame
{
	GENERATED_BODY()
	
public:
	USG_Incursion();

	UPROPERTY(VisibleAnywhere)
		int EnemiesKilled;
	
	UPROPERTY(VisibleAnywhere)
		int TotalPoints;

	UPROPERTY(VisibleAnywhere)
		int PlayerDeaths;

	UPROPERTY(VisibleAnywhere)
		int GamesPlayed;

	UPROPERTY(VisibleAnywhere)
		int GamesWon;
};
