// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "PC_PlayerController.h"
#include "W_HUD.h"

#include "A_UI_Manager.generated.h"

UCLASS()
class INCURSION_CPP_API AA_UI_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_UI_Manager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialise(APC_PlayerController* PlayerControllerRef);

	// HUD Widget Instance;
	UPROPERTY()
		class UW_HUD* WidgetHUD;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	APC_PlayerController* PlayerController;

	// HUD Class
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD> WidgetHUD_Class;
};
