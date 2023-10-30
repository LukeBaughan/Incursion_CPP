// Fill out your copyright notice in the Description page of Project Settings.

#include "AIC_Enemy.h"

#include "Kismet/GameplayStatics.h"

AAIC_Enemy::AAIC_Enemy() :
	BehaviorTreeAsset(nullptr)
{
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviourTreeOF(TEXT("/Game/Luke/Enemy/AI/BT_Enemy"));
	if (BehaviourTreeOF.Succeeded())
	{
		BehaviorTreeAsset = BehaviourTreeOF.Object;
	}
}

void AAIC_Enemy::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunBehaviorTree(BehaviorTreeAsset);
}