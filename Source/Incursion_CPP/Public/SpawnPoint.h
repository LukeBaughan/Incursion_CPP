// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BillboardComponent.h"
#include "Engine/StreamableManager.h"
#include "Engine/Texture2D.h"
#include "GameFramework/Actor.h"

#include "SpawnPoint.generated.h"

UCLASS()
class ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Billboard")
		class UBillboardComponent* BillboardComponent;
};
