// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "I_Character.h"

#include "C_Enemy.generated.h"

UCLASS()
class INCURSION_CPP_API AC_Enemy : public ACharacter, public II_Character
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Enemy();
	void TakeDamageCharacter(float Amount) override;

	USkeletalMeshComponent* BodyMesh;

private:
	FTransform BodyMeshSpawnTransform;
};
