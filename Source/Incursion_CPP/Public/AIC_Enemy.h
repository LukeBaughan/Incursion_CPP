// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h" 

#include "AIC_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class INCURSION_CPP_API AAIC_Enemy : public AAIController
{
	GENERATED_BODY()

public:
	AAIC_Enemy();
protected:
	void OnPossess(APawn* InPawn) override;
private:
	UBehaviorTree* BehaviorTreeAsset;
};
