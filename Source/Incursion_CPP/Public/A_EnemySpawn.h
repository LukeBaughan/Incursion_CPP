
#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

#include "A_EnemySpawn.generated.h"

UCLASS()
class INCURSION_CPP_API AA_EnemySpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_EnemySpawn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		UBoxComponent* BoxCollider;
};
