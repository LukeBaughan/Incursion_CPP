// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_GetEndGoal.generated.h"

UCLASS()
class INCURSION_CPP_API UBTS_GetEndGoal : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTS_GetEndGoal();
	// C++ Equivalent of Event Receive Activation AI
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "BP Keys")
		FBlackboardKeySelector EndGoalLocationKey;
};
