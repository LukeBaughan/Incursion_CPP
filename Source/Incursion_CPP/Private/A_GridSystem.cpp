// Fill out your copyright notice in the Description page of Project Settings.


#include "A_GridSystem.h"

#include "A_GridNode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AA_GridSystem::AA_GridSystem() :
	GridRows(4), GridColumns(4),
	SceneComponent(CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceenRoot")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent->SetupAttachment(RootComponent);
}

AA_GridSystem::~AA_GridSystem()
{
	// Destroys all grid nodes when the AA_GridSystem actor is being destroyed
	for (AActor* GridNode : AllGridNodes)
	{
		GridNode->Destroy();
	}
}


// Called when the game starts or when spawned
void AA_GridSystem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AA_GridSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called when an actor is done spawning into the world 
void AA_GridSystem::OnConstruction(const FTransform& Transform)
{
	// Calls the parents function
	Super::OnConstruction(Transform);

	FTransform SpawnTranform;
	SpawnTranform.SetLocation(FVector::Zero());

	// Attaches any existing grid nodes to the grid system (as when a grid system is placed, its grid nodes lose its parent actor)
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA_GridNode::StaticClass(), AllGridNodes);
	for (AActor* GridNode : AllGridNodes)
	{
		GridNode->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}

	CurrentGridSize = AllGridNodes.Num();
	MaxGridSize = GridRows + 1;

	// If there are less grid nodes than the maximum size, add more nodes
	if (CurrentGridSize < MaxGridSize)
	{
		/*for (int i = 0; i < GridRows; i++)
		{*/
		AActor* NewGridNode = GetWorld()->SpawnActor<AActor>(AA_GridNode::StaticClass(), this->GetActorTransform());
		NewGridNode->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		//}
	}

	int8 RowIndex = 0;

	for (AActor* GridNode : AllGridNodes)
	{
		float xLocation = RowIndex * 200.0f;
		GridNode->SetActorLocation(FVector(xLocation, 0.0f, 1.0f));
		++RowIndex;
	}
}

