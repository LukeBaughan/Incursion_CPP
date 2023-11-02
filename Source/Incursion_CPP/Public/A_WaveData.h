
#pragma once

#include "CoreMinimal.h"

#include "C_Enemy.h"
#include "Components/BillboardComponent.h"
#include "GameFramework/Actor.h"

#include "A_WaveData.generated.h"

USTRUCT(BlueprintType)
struct FWaveEnemies
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Struct Enemies")
		TArray<TSubclassOf<class AC_Enemy>> Enemies;
};
UCLASS()

class INCURSION_CPP_API AA_WaveData : public AActor
{
	GENERATED_BODY()
	
public:	
	AA_WaveData();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Billboard")
		class UBillboardComponent* BillboardComponent;

	// UE5 doesn't seem to allow Tarray of Tarray, instead this is a Tarray of struct containing a Tarray
	UPROPERTY(EditAnywhere, Category = "BP Wave Data")
		TArray<FWaveEnemies> AllWaveEnemies;

};