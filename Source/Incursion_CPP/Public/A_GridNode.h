// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "A_GridNode.generated.h"

UCLASS()
class INCURSION_CPP_API AA_GridNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_GridNode();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* PlaneMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
