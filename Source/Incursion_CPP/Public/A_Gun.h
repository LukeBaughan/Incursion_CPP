// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "BFL_Incursion.h"

#include "A_Gun.generated.h"

UCLASS()
class INCURSION_CPP_API AA_Gun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_Gun();

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialise(UCameraComponent* FirstPersonCamera);

	void ShootLineTrace(); // MAKE PRIVATE

private:

	UCameraComponent* PlayerCamera;
	UBFL_Incursion* BFL_Incursion;
};
