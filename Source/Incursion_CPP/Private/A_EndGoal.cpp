// Fill out your copyright notice in the Description page of Project Settings.

#include "A_EndGoal.h"

AA_EndGoal::AA_EndGoal() :
	BoxCollider(CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider")))
{
	BoxCollider->SetupAttachment(RootComponent);

	// Collsion
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BoxCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel5, ECollisionResponse::ECR_Block);
}