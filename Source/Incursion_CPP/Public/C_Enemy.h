// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "I_Character.h"
#include "I_Enemy.h"
#include "W_HealthBar.h"

#include "C_Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemy_OnGoalReached, uint8, LivesCostAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEnemy_OnDefeated, AC_Enemy*, Enemy, int, PointsAwardedAmount);

UCLASS()
class INCURSION_CPP_API AC_Enemy : public ACharacter, public II_Character, public II_Enemy
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Enemy();
	void Initialise();
	void TakeDamageCharacter(float DamageAmount) override;
	void DestroySelf();

	virtual bool GetIsDead() override;
	virtual bool GetPlayerInFollowRange() override;
	virtual bool GetPlayerInAttackRange() override;
	virtual bool GetAttackReady() override;
	virtual float GetAttackDamage() override;
	virtual void OnAttackExecuted() override;
	virtual USkeletalMeshComponent* GetBodyMesh() override;
	virtual USoundBase* GetAttackSound() override;
	virtual UAnimMontage* GetAttackAnimation() override;

	FEnemy_OnGoalReached OnGoalReached;
	FEnemy_OnDefeated OnDefeated;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		int PointsAwarded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		uint8 LivesCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float AttackRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float MaxWalkSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float MaxAcceleration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		UWidgetComponent* HealthBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float AttackDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		UAnimMontage* AttackAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		USoundBase* AttackSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		TArray<UAnimSequenceBase*> DeathAnimations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* FollowRangeCylinder;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Mesh")
		UStaticMeshComponent* AttackRangeCylinder;

protected:
	virtual void BeginPlay() override;

private:
	void EndAttackCooldown();
	void UpdateHealthBar();

	UFUNCTION()
		void CapsuleColliderOnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void FollowRangeCylinderOnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void FollowRangeCylinderOnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void AttackRangeCylinderOnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void AttackRangeCylinderOnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UCapsuleComponent* CapsuleCollider;
	USkeletalMeshComponent* BodyMesh;
	FTransform BodyMeshSpawnTransform;
	II_HealthBar* HealthBarInterface;
	UCharacterMovementComponent* MovementComponent;
	FTimerHandle TH_AttackCooldown;

	bool IsDead;
	float CurrentHealth;
	bool PlayerInFollowRange;
	bool PlayerInAttackRange;
	bool AttackReady;
};
