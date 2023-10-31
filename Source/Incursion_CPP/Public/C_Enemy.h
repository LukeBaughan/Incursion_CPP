// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "I_Character.h"
#include "W_HealthBar.h"

#include "C_Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemy_OnGoalReached, uint8, LivesCostAmount);

UCLASS()
class INCURSION_CPP_API AC_Enemy : public ACharacter, public II_Character
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Enemy();
	void Initialise();
	void TakeDamageCharacter(float DamageAmount) override;

	FEnemy_OnGoalReached OnGoalReached;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		int PointsAwarded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		uint8 LivesCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float MaxWalkSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float MaxAcceleration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		UWidgetComponent* HealthBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		USoundBase* HitSound;

private:
	void UpdateHealthBar();
	void DestroySelf();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UCapsuleComponent* CapsuleCollider;
	USkeletalMeshComponent* BodyMesh;
	FTransform BodyMeshSpawnTransform;
	II_HealthBar* HealthBarInterface;
	UCharacterMovementComponent* MovementComponent;

	bool IsDead;
	float CurrentHealth;
};
