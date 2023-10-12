// Fill out your copyright notice in the Description page of Project Settings.

#include "A_Gun.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AA_Gun::AA_Gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = nullptr;
	BFL_Incursion = NewObject<UBFL_Incursion>();

	GunMeshSpawnLocation = FVector::Zero();
	Damage = 25.0f;
	Range = 10000.0f;
	MaxAmmo = 5;
	CurrentAmmo = MaxAmmo;

	CurrentlyReloading = false;

	ShootTransform = FTransform(FRotator(0.0f, 90.0f, 0.0f), FVector(0.0f, 56.0f, 11.0f), FVector(1.0f, 1.0f, 1.0f));

	// Sets up the gun skeletal mesh component
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GunMeshFinder(TEXT("/Game/FPWeapon/Mesh/SK_FPGun"));

	if (GunMeshFinder.Succeeded())
	{
		GunMesh->SetSkeletalMesh(GunMeshFinder.Object);
		GunMesh->SetRelativeLocation(GunMeshSpawnLocation);
		UE_LOG(LogTemp, Warning, TEXT("Static mesh successfully set for AA_Gun."));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Failed to set static mesh for AA_Gun."));


	// Sets up the shoot transform arrow component
	ShootTransformArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Shoot Transform"));
	ShootTransformArrow->SetupAttachment(GunMesh);

	ShootTransformArrow->SetRelativeLocation(ShootTransform.GetLocation());
	ShootTransformArrow->SetRelativeRotation(ShootTransform.GetRotation());

	// Reload Sound
	static ConstructorHelpers::FObjectFinder<USoundBase> ReloadSoundFinder(TEXT("/Game/MilitaryWeapDark/Sound/Rifle/Rifle_Reload_Cue"));

	if (ReloadSoundFinder.Succeeded())
	{
		ReloadSound = ReloadSoundFinder.Object;
		UE_LOG(LogTemp, Warning, TEXT("ReloadSound successfully set for AA_Gun."));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Failed to set ReloadSound for AA_Gun."));
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

void AA_Gun::Initialise(UCameraComponent* FirstPersonCamera)
{
	PlayerCamera = FirstPersonCamera;
}

void AA_Gun::ShootOnceSequence()
{
	// Only shoots if the gun has ammo and isn't reloading
	if (CurrentAmmo > 0)
	{
		if (!CurrentlyReloading)
		{
			PlayShootAnimation();
			ShootLineTrace();
			// Decrease the current ammo by one after a shot is fired
			CurrentAmmo--;
			OnShotFired.Broadcast();
		}
	}
}

void AA_Gun::PlayShootAnimation()
{
	// Override in child classes
}

// Shoots the gun from the camera's position
void AA_Gun::ShootLineTrace()
{
	FVector ShotStartLocation = PlayerCamera->GetComponentLocation();
	FVector ShotEndLocation = ShotStartLocation + (PlayerCamera->GetForwardVector() * Range);

	BFL_Incursion->LineTraceShootEnemy(GetWorld(), ShotStartLocation, ShotEndLocation, Damage);
}

void AA_Gun::StartReloading()
{
	CurrentlyReloading = true;
	// Reload Sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadSound, GunMesh->GetComponentLocation(), 1.0f, 2.0f);
}