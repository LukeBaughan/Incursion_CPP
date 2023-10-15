// Fill out your copyright notice in the Description page of Project Settings.


#include "P_PlayerCamera.h"

// Sets default values
AP_PlayerCamera::AP_PlayerCamera():
	CameraComponent(CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component")))
{
 	// Set this pawn to call Tick() every frame.You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sets up the camera and makes it the pawn's root component
	CameraComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AP_PlayerCamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AP_PlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AP_PlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}