// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BFL_Incursion.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"

#include "A_Gun.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShotFired);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShotFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestReload);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadFinished);

UCLASS()
class INCURSION_CPP_API AA_Gun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_Gun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialise(UCameraComponent* FirstPersonCamera);

	void StartShoting();
	void EndShooting();
	void StartReloading();

	UFUNCTION()
		void FinishReloading();

	float MaxAmmo;
	float CurrentAmmo;
	float RateOfFire;

	bool CurrentlyReloading;
	USoundBase* ReloadSound;

	FOnShotFired OnShotFired;
	FOnShotFinished OnShotFinished;
	FOnRequestReload OnRequestReload;
	FOnReloadFinished OnReloadFinished;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		FVector GunMeshSpawnLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties")
		UArrowComponent* ShootTransformArrow;

	UPROPERTY(EditAnywhere, Category = "Properties")
		FTransform ShootTransform;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ShootLineTrace();

	float Damage;
	float Range;

	UBFL_Incursion* BFL_Incursion;
	UCameraComponent* PlayerCamera;
	UAnimSequence* ShootAnimSequence;


private:
	void ShootOnceSequence();
	void PlayShootAnimation();

	FTimerHandle TH_Shooting;
};
