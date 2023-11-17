
#pragma once

#include "CoreMinimal.h"

#include "BFL_Incursion.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "I_Tower.h"

#include "A_Tower.generated.h"

UCLASS()
class INCURSION_CPP_API AA_Tower : public AActor, public II_Tower
{
	GENERATED_BODY()
	
public:	
	AA_Tower();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
		void OnPlaced();
	virtual void OnPlaced_Implementation();
	UFUNCTION(BlueprintCallable)
		void OnPlacedSellOverride();

	virtual void ShowWalls_Implementation(FVector PlacedTowerPosition) override;
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
		USoundBase* ShootSound;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		UParticleSystem* ShootFX;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		UStaticMeshComponent* EnemyColliderMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		USphereComponent* AttackCollider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		float MuzzleRecoilDisplacement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float RateOfFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float Range;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		int Cost;

	USceneComponent* CurrentMuzzle;
	FVector CurrentMuzzleStartLocation;
	USceneComponent* CurrentShootLocation;
	USceneComponent* PlayerTowerPreviewLocationComponent;

protected:
	virtual void BeginPlay() override;

private:
	virtual void GetAllMuzzles();
	virtual void GetMuzzleToShoot();

	void LookAtEnemy();
	void ShootTarget();
	void RemoveFirstEnemyFromTargets();
	
	UFUNCTION()
		void ApplyBarrelRecoilTimelineFunction(float Alpha);

	UFUNCTION()
		void LookAtEnemyTimelineFunction(float Alpha);

	UFUNCTION()
		void AttackColliderOnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void AttackColliderOnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UBFL_Incursion* BFL_Incursion;

	bool PreviewMode;
	FVector PlayerTowerPreviewLocation;

	TArray<UStaticMeshComponent*> AllWalls;

	TArray<USceneComponent*> AllMuzzles;
	TArray<FVector> AllMuzzleStartLocations;

	TArray<USceneComponent*> AllShootLocations;

	TArray<AActor*> TargetsArray;
	FTimerHandle TH_ShootTarget;
	FVector TargetWorldLocation;
	FVector ShootWorldLocation;

	UTimelineComponent* TimelineLookAtEnemy;
	UCurveFloat* fCurveLookAtEnemy;
	FOnTimelineFloat LookAtEnemyTrack;

	UTimelineComponent* TimelineBarrelRecoil;
	UCurveFloat* fCurveBarrelRecoil;
	FOnTimelineFloat BarrelRecoilTrack;

	TSubclassOf<AA_Tower> SellTowerClass;
};
