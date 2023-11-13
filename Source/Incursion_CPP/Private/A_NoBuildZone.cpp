// Fill out your copyright notice in the Description page of Project Settings.


#include "A_NoBuildZone.h"

// Sets default values
AA_NoBuildZone::AA_NoBuildZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AA_NoBuildZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AA_NoBuildZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

