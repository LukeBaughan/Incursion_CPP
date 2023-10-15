// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Gun_Shotgun.h"

AA_Gun_Shotgun::AA_Gun_Shotgun() : AA_Gun()
{
	Damage = 9.0f;
	Range = 1000.0f;
	RateOfFire = 1.03f;
	MaxAmmo = 6;
	PelletAmount = 12;
	MaxPelletOffset = 0.1f;

	// Sets up the gun skeletal mesh component

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GunMeshAsset(TEXT("/Game/MilitaryWeapSilver/Weapons/Shotgun_A"));

	if (GunMeshAsset.Succeeded())
		GunMesh->SetSkeletalMesh(GunMeshAsset.Object);
	else
		UE_LOG(LogTemp, Warning, TEXT("AA_Gun_Shotgun: Failed to set GunMesh"));

	// Gets Assault Rifle Fire Animation Montage

	static ConstructorHelpers::FObjectFinder<UAnimSequence> ShootAnimSequenceFinder(TEXT("/Game/MilitaryWeapSilver/Weapons/Animations/Fire_Shotgun_W"));
	if (ShootAnimSequenceFinder.Succeeded())
		ShootAnimSequence = ShootAnimSequenceFinder.Object;
	else
		UE_LOG(LogTemp, Warning, TEXT("AA_Gun_Shotgun: Failed to set ShootAnimSequence"));
}

// Shoots multiple line traces in a filtered random directions
void AA_Gun_Shotgun::ShootLineTrace()
{
	for (int8 i = 0; i < PelletAmount; ++i)
	{
		FVector ShotStartLocation = PlayerCamera->GetComponentLocation();

		FVector PlayerCameraDirection = PlayerCamera->GetForwardVector();

		FVector ShotEndLocation = (FVector(PlayerCameraDirection.X + BFL_Incursion->GetAveragePelletOffset(MaxPelletOffset),
			PlayerCameraDirection.Y + BFL_Incursion->GetAveragePelletOffset(MaxPelletOffset), PlayerCameraDirection.Z + BFL_Incursion->GetAveragePelletOffset(MaxPelletOffset))
			* Range) + ShotStartLocation;

		BFL_Incursion->LineTraceShootEnemy(GetWorld(), ShotStartLocation, ShotEndLocation, Damage);
	}
}