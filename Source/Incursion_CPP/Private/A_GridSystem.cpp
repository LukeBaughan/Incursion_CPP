// Fill out your copyright notice in the Description page of Project Settings.


#include "A_GridSystem.h"
#include "A_GridNode.h"

// Sets default values
AA_GridSystem::AA_GridSystem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AA_GridSystem::BeginPlay()
{
	Super::BeginPlay();

}

void AA_GridSystem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Destroy any child actors when the AA_GridSystem actor is being destroyed
	TArray<AActor*> ChildActors;
	GetAttachedActors(ChildActors);

	for (AActor* ChildActor : ChildActors)
	{
		ChildActor->Destroy();
	}

	Super::EndPlay(EndPlayReason);
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

	// Creates an array of type AActor pointer
	//TArray<AActor*> ChildActors;
	// Stores all of the grid system's child actor pointers in the ChildActor array
	//GetAttachedActors(ChildActors);

	FTransform SpawnTranform;
	SpawnTranform.SetLocation(FVector(0.0f, 0.0f, 1.0f));

	AActor* NewChildActor = GetWorld()->SpawnActor<AActor>(AA_GridNode::StaticClass(), SpawnTranform);
	NewChildActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

	//// Creates the grid
	//for (int Row = 0; Row < Rows; Row++)
	//{
	//	for (int Column = 0; Column < Columns; Column++)
	//	{
	//		// Spawns the next child actor, sets it's location and then attaches it to the parent (the Grid system)
	//		FTransform SpawnTranform;
	//		SpawnTranform.SetLocation(FVector(Column * 200.0f, Row * 200.0f, 1.0f));

	//		AActor* NewChildActor = GetWorld()->SpawnActor<AActor>(AA_GridNode::StaticClass(), SpawnTranform);
	//		NewChildActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

	//		UE_LOG(LogTemp, Warning, TEXT("column loop"));
	//	}
	//	UE_LOG(LogTemp, Warning, TEXT("row loop"));
	//}
}

