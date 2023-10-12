// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Gun_AssaultRifle.h"

AA_Gun_AssaultRifle::AA_Gun_AssaultRifle() : AA_Gun()
{
	// Sets up the gun skeletal mesh component

	Damage = 25.0f;
	Range = 10000.0f;
	RateOfFire = 0.09f;
	MaxAmmo = 30;

	// Gets Assault Rifle Skeleton Mesh

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GunMeshAsset(TEXT("/Game/MilitaryWeapDark/Weapons/Assault_Rifle_B"));

	if (GunMeshAsset.Succeeded())
		GunMesh->SetSkeletalMesh(GunMeshAsset.Object);
	else
		UE_LOG(LogTemp, Warning, TEXT("Failed to set static mesh for AA_Gun_AssaultRifle."));

	// Gets Assault Rifle Fire Animation Montage

	static ConstructorHelpers::FObjectFinder<UAnimSequence> ShootAnimSequenceFinder(TEXT("/Game/MilitaryWeapDark/Weapons/Anims/Fire_Rifle_W"));
	if (ShootAnimSequenceFinder.Succeeded())
		ShootAnimSequence = ShootAnimSequenceFinder.Object;
	else
		UE_LOG(LogTemp, Warning, TEXT("Failed to set ShootAnimSequence for AA_Gun_AssaultRifle."));

}