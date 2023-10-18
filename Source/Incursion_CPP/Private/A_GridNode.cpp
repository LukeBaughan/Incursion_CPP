// Fill out your copyright notice in the Description page of Project Settings.


#include "A_GridNode.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AA_GridNode::AA_GridNode(): 
    PlaneMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Component")))
{
	PlaneMesh->SetupAttachment(RootComponent);
}