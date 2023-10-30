// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

#include "A_EndGoal.generated.h"

UCLASS()
class INCURSION_CPP_API AA_EndGoal : public AActor
{
	GENERATED_BODY()

public:
	AA_EndGoal();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		UBoxComponent* BoxCollider;
};
