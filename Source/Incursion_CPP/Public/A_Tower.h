
#pragma once

#include "CoreMinimal.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"

#include "A_Tower.generated.h"

UCLASS()
class INCURSION_CPP_API AA_Tower : public AActor
{
	GENERATED_BODY()
	
public:	
	AA_Tower();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		USceneComponent* TowerSceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		USceneComponent* BaseSceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float RateOfFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float Range;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		int Cost;
};
