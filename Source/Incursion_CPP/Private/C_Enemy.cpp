// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Enemy.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AC_Enemy::AC_Enemy() :
	BodyMeshSpawnTransform(FTransform(FRotator::ZeroRotator, FVector(0.0f, 0.0f, -90.0f), FVector::OneVector)),
	BodyMesh(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body Mesh")))
{
	// Sets up the body mesh
	BodyMesh->SetupAttachment(GetCapsuleComponent());	
	BodyMesh->SetRelativeTransform(BodyMeshSpawnTransform);
	BodyMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshOF(TEXT("/Game/Characters/Mannequins/Meshes/SKM_Manny"));
	if (BodyMeshOF.Succeeded())
	{
		BodyMesh->SetSkeletalMesh(BodyMeshOF.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("C_Enemy: Unable to set BodyMesh"));
	}
}

void AC_Enemy::TakeDamageCharacter(float Amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("C_Enemy: TakeDamage Called"));
}