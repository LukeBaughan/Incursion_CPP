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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayer_RequestPauseGame, bool, PauseGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRequestSkipCountdown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayer_RequestToggleStore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayer_RequestPlaceTower);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoAmountChanged, int8, MaxAmmo, int8, CurrentAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerOnDamageTaken, float, PlayerCurrentHealth, float, PlayerMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerOnDead);

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

	UFUNCTION()
		void SetCurrentlyHoldingTower(bool HoldingTower);


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Weapon")
		FTransform AssaultRifleTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Weapon")
		FTransform ShotgunTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Weapon")
		USkeletalMeshComponent* GunPositionMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		USoundBase* DamageRecievedSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		USceneComponent* TowerPreviewLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		USkeletalMeshComponent* ArmsMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		TSubclassOf<class UAnimInst_Player_Base> AnimInstClassBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		TSubclassOf<class UAnimInst_Player_Base> AnimInstClassAssaultRifle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		TSubclassOf<class UAnimInst_Player_Base> AnimInstClassShotgun;

	FPlayer_RequestPauseGame RequestPauseGame;
	FPlayerOnDamageTaken OnDamageTaken;
	FPlayerOnDead OnDead;
	FRequestSkipCountdown RequestSkipCountdown;
	FPlayer_RequestToggleStore RequestToggleStore;
	FPlayer_RequestPlaceTower RequestPlaceTower;
	FOnAmmoAmountChanged OnAmmoAmountChanged;

	UCapsuleComponent* CapsuleCollider;

	float CurrentHealth;
	bool IsDead = false;

private:
	// Camera
	void LookLeftRight(float AxisValue);
	void LookUpDown(float AxisValue);

	void SkipCountdown();

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

	void PauseGameActionPressed();
	void ToggleStoreActionPressed();

	// Movement

	void MoveForwardBackwards(float AxisValue);
	void MoveLeftRight(float AxisValue);
	void StartPerformSprint();
	void EndPerformSprint();
	void PerformJump();

	void PerformPrimaryActionPressed();
	void PerformPrimaryActionReleased();

	void SetSprint(bool Sprint);

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
	AA_Gun* Gun;
	FTransform GunTransform;
	FTransform GunPositonMeshTransform;
	FActorSpawnParameters GunSpawnParameters;

	UAnimInst_Player_Base* AnimInst;

	bool CurrentlyShooting;
	FTimerHandle TH_Shooting;

	bool CurrentlyHoldingTower;
};
