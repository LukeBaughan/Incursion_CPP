// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"

// Sets default values
ASpawnPoint::ASpawnPoint():
	BillboardComponent(CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComponent")))
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Creates the editor viewport icon and attaches it to the root component
	BillboardComponent->SetupAttachment(RootComponent);
}