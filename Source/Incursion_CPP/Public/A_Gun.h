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

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	AssaultRifle,
	Shotgun
};

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		EWeaponType WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UArrowComponent* ShootTransformArrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UAnimSequence* ShootAnimSequence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		USoundBase* ReloadSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float Range;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float RateOfFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		int MaxAmmo;

	int8 CurrentAmmo;

	bool CurrentlyReloading;

	FOnShotFired OnShotFired;
	FOnShotFinished OnShotFinished;
	FOnRequestReload OnRequestReload;
	FOnReloadFinished OnReloadFinished;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ShootLineTrace();

	UBFL_Incursion* BFL_Incursion;
	UCameraComponent* PlayerCamera;

private:
	void ShootOnceSequence();
	void PlayShootAnimation();

	FVector GunMeshSpawnLocation;
	FTransform ShootArrowSpawnLocation;
	FTimerHandle TH_Shooting;
};