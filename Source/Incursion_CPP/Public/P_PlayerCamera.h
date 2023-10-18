// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"

#include "P_PlayerCamera.generated.h"

UCLASS()
class INCURSION_CPP_API AP_PlayerCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AP_PlayerCamera();	

private:
	UCameraComponent* CameraComponent;
};
