// Fill out your copyright notice in the Description page of Project Settings.

#include "A_Gun.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AA_Gun::AA_Gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sets up the gun skeletal mesh component
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GunMeshAsset(TEXT("/Game/FPWeapon/Mesh/SK_FPGun"));

	if (GunMeshAsset.Succeeded())
	{
		GunMesh->SetSkeletalMesh(GunMeshAsset.Object);
		GunMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		UE_LOG(LogTemp, Warning, TEXT("Static mesh successfully set for AA_Gun."));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Failed to set static mesh for AA_Gun."));


	// Sets up the shoot transform arrow component
	ShootTransform = CreateDefaultSubobject<UArrowComponent>(TEXT("Shoot Transform"));
	ShootTransform->SetupAttachment(GunMesh);

	ShootTransform->SetRelativeLocation(FVector(0.0f, 56.0f, 11.0f));
	ShootTransform->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

}

// Called when the game starts or when spawned
void AA_Gun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AA_Gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

