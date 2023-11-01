
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_WaveManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaveManager_OnRequestLoseLives, uint8, Amount);

UCLASS()
class INCURSION_CPP_API AA_WaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_WaveManager();
	void Initialise();
	void BeginWaveCountdown();

	FWaveManager_OnRequestLoseLives OnRequestLoseLives;

private:
	void GetEnemySpawnLocation();
	void SpawnEnemy(TSubclassOf<class AC_Enemy> EnemyClass);

	UFUNCTION()
		void OnEnemyGoalReached(uint8 LivesCost);

	UFUNCTION()
		void OnEnemyDefeated(AC_Enemy* Enemy, int PointsRewarded);

	TSubclassOf<class AC_Enemy> EnemyClasses[1];
	FVector EnemySpawnLocation;
	FActorSpawnParameters EnemySpawnParameters;
};

UENUM(BlueprintType)
enum E_EnemyClass
{
	Standard UMETA(DisplayName = "Standard")
};