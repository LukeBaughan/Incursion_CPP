// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ChildActorComponent.h"
#include "A_GridSystem.generated.h"

UCLASS()
class INCURSION_CPP_API AA_GridSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_GridSystem();
	~AA_GridSystem();

	UPROPERTY(EditAnywhere, Category = "Grid Size")
	int GridRows = 4;
	UPROPERTY(EditAnywhere, Category = "Grid Size")
	int GridColumns = 4;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int CurrentGridSize = 0;
	int MaxGridSize = 1;
	TArray<AActor*> AllGridNodes;

	USceneComponent* SceneComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called when the actor is being destroyed
	virtual void OnConstruction(const FTransform& Transform) override;
};
