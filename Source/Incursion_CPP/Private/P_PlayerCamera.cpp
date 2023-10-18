// Fill out your copyright notice in the Description page of Project Settings.


#include "P_PlayerCamera.h"

// Sets default values
AP_PlayerCamera::AP_PlayerCamera():
	CameraComponent(CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component")))
{
	// Sets up the camera and makes it the pawn's root component
	CameraComponent->SetupAttachment(RootComponent);
}