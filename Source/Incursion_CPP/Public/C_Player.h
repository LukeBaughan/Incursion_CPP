// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "A_Gun.h"
#include "AnimInst_Player_Base.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "I_Character.h"

#include "C_Player.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoAmountChanged, int8, MaxAmmo, int8, CurrentAmmo);

UCLASS()
class AC_Player : public ACharacter, public II_Character
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Player();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Initialise(TSubclassOf<class AA_Gun> GunSpawnClass);
	void CallOnAmmoAmountChangedED();
	virtual void TakeDamageCharacter(float DamageAmount) override;
	virtual bool GetIsDead() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Weapon")
		FTransform AssaultRifleTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Weapon")
		FTransform ShotgunTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Weapon")
		USkeletalMeshComponent* GunPositionMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Camera")
		UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		USkeletalMeshComponent* ArmsMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		TSubclassOf<class UAnimInst_Player_Base> AnimInstClassBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		TSubclassOf<class UAnimInst_Player_Base> AnimInstClassAssaultRifle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		TSubclassOf<class UAnimInst_Player_Base> AnimInstClassShotgun;

	FOnAmmoAmountChanged OnAmmoAmountChanged;

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

	void SetUpAnimInstanceType();
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

	UCapsuleComponent* CapsuleCollider;
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
	AA_Gun* Gun;
	FTransform GunTransform;
	FTransform GunPositonMeshTransform;
	FActorSpawnParameters GunSpawnParameters;

	UAnimInst_Player_Base* AnimInst;

	bool CurrentlyShooting;
	FTimerHandle TH_Shooting;
};
