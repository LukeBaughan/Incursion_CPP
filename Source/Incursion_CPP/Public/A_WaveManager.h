
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_WaveManager.generated.h"

UCLASS()
class INCURSION_CPP_API AA_WaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_WaveManager();
	void Initialise();
	void BeginWaveCountdown();

private:
	void GetEnemySpawnLocation();
	void SpawnEnemy(TSubclassOf<class AC_Enemy> EnemyClass);

	TSubclassOf<class AC_Enemy> EnemyClasses[1];
	FVector EnemySpawnLocation;
	FActorSpawnParameters EnemySpawnParameters;
};

UENUM(BlueprintType)
enum E_EnemyClass
{
	Standard UMETA(DisplayName = "Standard")
};