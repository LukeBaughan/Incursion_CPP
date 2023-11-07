
#pragma once

#include "CoreMinimal.h"

#include "A_WaveData.h"
#include "GameFramework/Actor.h"
#include "W_HUD_SkipCountdown.h"
#include "W_HUD_Timer.h"

#include "A_WaveManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaveManager_OnRequestLoseLives, uint8, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaveManager_OnRequestPoints, int, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWaveManager_OnWaveBegin, uint8, CurrentWave, uint8, MaxWave);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaveManager_OnWaveEnded);

// DEPRECIATED: IMPORTANT: Increase the size of EnemyClasses when adding to E_EnemyClass 
UENUM(BlueprintType)
enum E_EnemyClass
{
	Standard UMETA(DisplayName = "Standard"),
	Runner UMETA(DisplayName = "Runner"),
	Maverick UMETA(DisplayName = "Maverick"),
	Heavy UMETA(DisplayName = "Heavy"),
	Behemoth UMETA(DisplayName = "Behemoth")
};

UCLASS()
class INCURSION_CPP_API AA_WaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_WaveManager();
	void Initialise(UW_HUD_Timer* WidgetHUD_TimerRef, UW_HUD_SkipCountdown* WidgetHUD_SkipCountdownRef);
	void BeginWaveCountdown();

	UFUNCTION()
		void SkipCountdown();

	FWaveManager_OnRequestLoseLives OnRequestLoseLives;
	FWaveManager_OnRequestPoints OnRequestPoints;
	FWaveManager_OnWaveBegin OnWaveBegin;
	FWaveManager_OnWaveEnded OnWaveEnded;

private:
	void GetEnemyClassReference(E_EnemyClass EnemyClass, FString EnemyBP_FileName);
	void GetWaveData();
	void GetEnemySpawnLocation();
	void Countdown();
	void BeginWave();
	void DecideSpawnEnemyClass();
	void SpawnEnemy(TSubclassOf<class AC_Enemy> EnemyClass);
	void IncrementEnemiesDefeatedOrReachedGoal();

	UFUNCTION()
		void OnEnemyGoalReached(uint8 LivesCost);

	UFUNCTION()
		void OnEnemyDefeated(AC_Enemy* Enemy, int PointsRewarded);

	UW_HUD_Timer* WidgetHUD_Timer;
	UW_HUD_SkipCountdown* WidgetHUD_SkipCountdown;

	int8 MaxCountdownTime;
	int8 CurrentCountdownTime;
	FTimerHandle TH_Countdown;
	TArray<FWaveEnemies> AllWaveEnemies;
	TArray<TSubclassOf<class AC_Enemy>> CurrentWaveEnemies;
	TSubclassOf<class AC_Enemy> EnemyClasses[5];
	FVector EnemySpawnLocation;
	FActorSpawnParameters EnemySpawnParameters;
	int8 CurrentWave;
	int8 EnemySpawnIndex;
	int8 TotalNumberOfEnemiesThisWave;
	int8 EnemiesDefeatedOrReachedGoalThisWave;
	TArray<AC_Enemy*> DeadEnemies;
	FTimerHandle TH_SpawningEnemies;
	float EnemySpawnRate;
};

