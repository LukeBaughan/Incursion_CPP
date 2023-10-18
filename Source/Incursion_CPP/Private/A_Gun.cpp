// Fill out your copyright notice in the Description page of Project Settings.

#include "A_Gun.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AA_Gun::AA_Gun() :
	BFL_Incursion(NewObject<UBFL_Incursion>()),
	PlayerCamera(nullptr),
	ShootAnimSequence(nullptr),
	GunMeshSpawnLocation(FVector::Zero()),

	Damage(25.0f),
	Range(10000.0f),
	RateOfFire(0.25f),
	MaxAmmo(15),
	CurrentAmmo(0),
	CurrentlyReloading(false),

	ShootArrowSpawnLocation(FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::OneVector)),
	GunMesh(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"))),
	ShootTransformArrow(CreateDefaultSubobject<UArrowComponent>(TEXT("Shoot Transform")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sets up the gun skeletal mesh component
	GunMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GunMeshFinder(TEXT("/Game/FPWeapon/Mesh/SK_FPGun"));

	if (GunMeshFinder.Succeeded())
	{
		GunMesh->SetSkeletalMesh(GunMeshFinder.Object);
		GunMesh->SetRelativeLocation(GunMeshSpawnLocation);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Failed to set static mesh for AA_Gun."));

	// Sets up the shoot transform arrow component
	ShootTransformArrow->SetupAttachment(GunMesh);
	ShootTransformArrow->SetRelativeTransform(ShootArrowSpawnLocation);
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
	CurrentAmmo = MaxAmmo;
}

// Loops the shoot function for full-auto weapons
void AA_Gun::StartShoting()
{
	ShootOnceSequence();
	GetWorldTimerManager().SetTimer(TH_Shooting, this, &AA_Gun::ShootOnceSequence, RateOfFire, true);
}

void AA_Gun::EndShooting()
{
	GetWorldTimerManager().ClearTimer(TH_Shooting);
	OnShotFinished.Broadcast();
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
			--CurrentAmmo;
			OnShotFired.Broadcast();
		}
	}
	else
	{
		OnShotFinished.Broadcast();
		// Auto reloads if the mag is empty
		if (!CurrentlyReloading)
		{
			OnRequestReload.Broadcast();
		}
	}
}

void AA_Gun::PlayShootAnimation()
{
	// Override animation sequence in child classes
	if (ShootAnimSequence)
	{
		GunMesh->PlayAnimation(ShootAnimSequence, false);
	}
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
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadSound, GunMesh->GetComponentLocation());
}

void AA_Gun::FinishReloading()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadSound, GunMesh->GetComponentLocation(), 1.0f, 2.0f);
	CurrentAmmo = MaxAmmo;
	CurrentlyReloading = false;
	OnReloadFinished.Broadcast();
}