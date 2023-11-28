// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_GetEndGoal.h"

#include "AIController.h"
#include "A_EndGoal.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTS_GetEndGoal::UBTS_GetEndGoal()
{
	bNotifyBecomeRelevant = true;
}

void UBTS_GetEndGoal::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(EndGoalLocationKey.SelectedKeyName,
		UGameplayStatics::GetActorOfClass(OwnerComp.GetAIOwner()->GetWorld(), AA_EndGoal::StaticClass())->GetRootComponent()->GetComponentLocation());
}