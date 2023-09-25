// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "A_Gun.h"

#include "C_Player.generated.h"

UCLASS()
class AC_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Player();

	void Initialise();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		UCameraComponent* CameraComponent;

	// Gun
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		AA_Gun* Gun;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		USkeletalMeshComponent* GunPositionMesh;

	UPROPERTY(EditAnywhere, Category = "Weapon")
		FTransform GunPositonMeshTransform;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	// Camera
	void LookLeftRight(float AxisValue);
	void LookUpDown(float AxisValue);

	FVector CameraSpawnLocation;
	float MouseSensitivity = 1.0f;

	// Movement

	UCharacterMovementComponent* MovementComponent;

	void MoveForwardBackwards(float AxisValue);
	void MoveLeftRight(float AxisValue);
	void StartPerformSprint();
	void EndPerformSprint();
	void PerformJump();

	void SetSprint(bool Sprint);

	float ForwardWalkAmount = 0.0f;

	float WalkSpeed = 600.0f;
	float WalkAcceleration = 2048.0f;

	float SprintSpeed = 1200.0f;
	float SprintAcceleration = 4048.0f;

	bool IsDead = false;
};
