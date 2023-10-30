// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "I_Character.h"
#include "W_HealthBar.h"

#include "C_Enemy.generated.h"

UCLASS()
class INCURSION_CPP_API AC_Enemy : public ACharacter, public II_Character
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Enemy();
	void TakeDamageCharacter(float DamageAmount) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		UWidgetComponent* HealthBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		USoundBase* HitSound;

protected:
	// TEMP
	virtual void BeginPlay() override;

private:
	void UpdateHealthBar();

	UCapsuleComponent* CapsuleCollider;
	USkeletalMeshComponent* BodyMesh;
	FTransform BodyMeshSpawnTransform;
	II_HealthBar* HealthBarInterface;
	UCharacterMovementComponent* MovementComponent;

	bool IsDead;
	float CurrentHealth;
};
