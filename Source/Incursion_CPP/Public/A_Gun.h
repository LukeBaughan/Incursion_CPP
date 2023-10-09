// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "BFL_Incursion.h"

#include "A_Gun.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShotFired);

UCLASS()
class INCURSION_CPP_API AA_Gun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_Gun();

	float MaxAmmo;
	float CurrentAmmo;

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

	float Damage;
	float Range;

	virtual void PlayShootAnimation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnShotFired OnShotFired;

	void Initialise(UCameraComponent* FirstPersonCamera);

	void ShootOnceSequence(); // MAKE PRIVATE LATER

private:

	UCameraComponent* PlayerCamera;
	UBFL_Incursion* BFL_Incursion;

	bool Reloading;

	void ShootLineTrace(); 
};
