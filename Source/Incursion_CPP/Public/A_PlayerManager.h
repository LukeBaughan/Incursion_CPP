// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "C_Player.h"
#include "SpawnPoint.h"
#include "PC_PlayerController.h"

#include "A_PlayerManager.generated.h"

UCLASS()
class INCURSION_CPP_API AA_PlayerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_PlayerManager();

	void Initialise(TSubclassOf<class AA_Gun> SpawnWeapon);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	void SetUpPlayerController();
	void SetUpPlayer();

	APC_PlayerController* PlayerController;
	AC_Player* PlayerCharacter;

	ASpawnPoint* SpawnPoint;
	FVector PlayerSpawnLocation;
	FActorSpawnParameters PlayerSpawnParameters;

	TSubclassOf<class AA_Gun> PlayerSpawnWeaponClass;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
