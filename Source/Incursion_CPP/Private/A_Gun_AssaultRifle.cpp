// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Gun_AssaultRifle.h"

AA_Gun_AssaultRifle::AA_Gun_AssaultRifle() : AA_Gun()
{
	// Sets up the gun skeletal mesh component

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GunMeshAsset(TEXT("/Game/MilitaryWeapDark/Weapons/Assault_Rifle_B"));

	if (GunMeshAsset.Succeeded())
	{
		GunMesh->SetSkeletalMesh(GunMeshAsset.Object);
		UE_LOG(LogTemp, Warning, TEXT("Static mesh successfully set for AA_Gun_AssaultRifle."));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Failed to set static mesh for AA_Gun_AssaultRifle."));
}