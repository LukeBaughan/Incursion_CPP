// Fill out your copyright notice in the Description page of Project Settings.


#include "A_GridNode.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

// Sets default values
AA_GridNode::AA_GridNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Sets up the plane mesh
    PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Component"));
    PlaneMesh->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMeshAsset(TEXT("StaticMesh'/Game/StarterBundle/ModularSci_Int/Meshes/SM_FloorPanel_A_AlteredMesh.SM_FloorPanel_A_AlteredMesh'"));

    if (PlaneMeshAsset.Succeeded())
    {
        PlaneMesh->SetStaticMesh(PlaneMeshAsset.Object);
        PlaneMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        UE_LOG(LogTemp, Warning, TEXT("Static mesh successfully set for AA_GridNode."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to set static mesh for AA_GridNode. Check the asset path."));
    }
}

// Called when the game starts or when spawned
void AA_GridNode::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AA_GridNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

