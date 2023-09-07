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

	UPROPERTY(EditAnywhere, Category = "Grid Size")
	int Rows = 1;
	UPROPERTY(EditAnywhere, Category = "Grid Size")
	int Columns = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UChildActorComponent* GridNodeComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called when the actor is being destroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnConstruction(const FTransform& Transform) override;
};
