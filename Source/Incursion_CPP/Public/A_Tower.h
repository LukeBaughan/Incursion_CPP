
#pragma once

#include "CoreMinimal.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "I_Tower.h"

#include "A_Tower.generated.h"

UCLASS()
class INCURSION_CPP_API AA_Tower : public AActor, public II_Tower
{
	GENERATED_BODY()
	
public:	
	AA_Tower();

	void OnPlaced();
	virtual void ShowWalls(FVector PlacedTowerPosition) override;
	void ShowWall(UStaticMeshComponent* Wall);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		USceneComponent* TowerSceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		USceneComponent* WallsSceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* WallBack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* WallFront;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* WallLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* WallRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* WallBackLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* WallBackRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* WallFrontLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* WallFrontRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		USceneComponent* BaseSceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		USceneComponent* BodySceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* BodyMeshLower;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* BodyMeshUpper;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UArrowComponent* ArrowComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		USceneComponent* TurretSceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		USceneComponent* MuzzlesSceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* MuzzleMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		USceneComponent* ShootLocationSceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		UBoxComponent* EnemyCollider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		USphereComponent* AttackCollider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float RateOfFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float Range;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		int Cost;

private:
	virtual void GetAllMuzzles();

	bool PreviewMode;

	TArray<UStaticMeshComponent*> AllWalls;

	TArray<USceneComponent*> AllMuzzles;
	TArray<FVector> AllMuzzleStartLocations;

	TArray<USceneComponent*> AllShootLocations;
};
