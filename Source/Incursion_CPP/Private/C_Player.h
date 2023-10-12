// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "A_Gun.h"
#include "AnimInst_Player_Base.h"

#include "C_Player.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoAmountChanged, int, MaxAmmo, int, CurrentAmmo);

UCLASS()
class AC_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Arms")
		USkeletalMeshComponent* ArmsMesh;

	// Gun
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		AA_Gun* Gun;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		USkeletalMeshComponent* GunPositionMesh;

public:	

	FOnAmmoAmountChanged OnAmmoAmountChanged;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Initialise(TSubclassOf<class AA_Gun> GunSpawnClass);
	void CallOnAmmoAmountChangedED();

private:

	// Capsule Collider
	float CapsuleHalfHeightSize;
	float CapsuleRadiusSize;

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

	void PerformPrimaryAction();

	void SetSprint(bool Sprint);

	float ForwardWalkAmount = 0.0f;

	float WalkSpeed = 600.0f;
	float WalkAcceleration = 2048.0f;

	float SprintSpeed = 1200.0f;
	float SprintAcceleration = 4048.0f;

	// Other
	bool IsDead = false;

	// Arms
	FTransform ArmsMeshTransform;

	//Gun
	FTransform GunPositonMeshTransform;
	FActorSpawnParameters GunSpawnParameters;
	UAnimInst_Player_Base* AnimInstPlayer;

	UFUNCTION()
		void OnGunShotFired();

	void ReloadGun();
};
