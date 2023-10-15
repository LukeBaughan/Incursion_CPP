// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "A_Gun.h"
#include "AnimInst_Player_Base.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "C_Player.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoAmountChanged, int8, MaxAmmo, int8, CurrentAmmo);

UCLASS()
class AC_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Player();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Initialise(TSubclassOf<class AA_Gun> GunSpawnClass);
	void CallOnAmmoAmountChangedED();

	FOnAmmoAmountChanged OnAmmoAmountChanged;

	UPROPERTY(BlueprintReadWrite, Category = "Gun")
		FTransform GunTransform;

	// SET IN BLUEPRINT
	UPROPERTY(BlueprintReadWrite, Category = "Gun")
		FTransform AssaultRifleTransform;

	// SET IN BLUEPRINT
	UPROPERTY(BlueprintReadWrite, Category = "Gun")
		FTransform ShotgunTransform;

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

private:
	// Camera
	void LookLeftRight(float AxisValue);
	void LookUpDown(float AxisValue);

	// Gun

	UFUNCTION()
		void OnGunShotFired();

	void ResetShooting();

	UFUNCTION()
		void StopArmsShootAnimation();

	UFUNCTION()
		void ReloadGun();

	UFUNCTION()
		void OnGunReloadFinished();

	void SetUpAnimInstanceType(TSubclassOf<class AA_Gun> GunSpawnClass);
	void SetUpAnimInst(TSubclassOf<class UAnimInst_Player_Base> AnimInst, FTransform GunTranform);

	// Movement

	void MoveForwardBackwards(float AxisValue);
	void MoveLeftRight(float AxisValue);
	void StartPerformSprint();
	void EndPerformSprint();
	void PerformJump();

	void PerformPrimaryActionPressed();
	void PerformPrimaryActionReleased();

	void SetSprint(bool Sprint);

	bool IsDead = false;

	// Capsule Collider

	float CapsuleHalfHeightSize;
	float CapsuleRadiusSize;

	// Movement

	FVector CameraSpawnLocation;
	float MouseSensitivity;
	UCharacterMovementComponent* MovementComponent;

	float ForwardWalkAmount;

	float WalkSpeed;
	float WalkAcceleration;

	float SprintSpeed;
	float SprintAcceleration;

	// Arms
	FTransform ArmsMeshTransform;

	//Gun
	FTransform GunPositonMeshTransform;
	FActorSpawnParameters GunSpawnParameters;

	UAnimInst_Player_Base* AnimInst;
	TSubclassOf<class UAnimInst_Player_Base> AnimInstClassBase, AnimInstClassAssaultRifle, AnimInstClassShotgun;

	bool CurrentlyShooting;
	FTimerHandle TH_Shooting;
};
