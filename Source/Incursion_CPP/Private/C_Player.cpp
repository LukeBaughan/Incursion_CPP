// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Player.h"

#include "A_Gun_Shotgun.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AC_Player::AC_Player() :
	MouseSensitivity(1.0f),
	ForwardWalkAmount(0.0f),
	WalkSpeed(600.0f),
	WalkAcceleration(2048.0f),
	SprintSpeed(1200.0f),
	SprintAcceleration(4048.0f),
	MovementComponent(GetCharacterMovement()),

	CurrentlyShooting(false),
	MaxHealth(100.0f),
	CurrentHealth(MaxHealth),

	CapsuleCollider(GetCapsuleComponent()),
	CapsuleHalfHeightSize(96.0f),
	CapsuleRadiusSize(55.0f),

	CameraSpawnLocation(FVector(-39.5f, 0.0f, 64.2f)),
	CameraComponent(CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"))),

	TowerPreviewLocation(CreateDefaultSubobject<USceneComponent>(TEXT("Tower Preview Location"))),

	DamageRecievedSound(nullptr),

	ArmsMeshTransform(FTransform(FRotator(1.73f, -80.15f, -6.0f), FVector(-5.33f, -15.25f, -164.54f), FVector::One())),
	ArmsMesh(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms Mesh"))),

	AnimInst(nullptr),

	Gun(nullptr),
	GunPositonMeshTransform(FTransform(FRotator(-2.5f, 265.8f, -358.5f), FVector(3.7f, 12.2f, -21.5f), FVector::One())),
	GunPositionMesh(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Position Mesh"))),

	CurrentlyHoldingTower(false)
{
	CapsuleCollider->SetCapsuleHalfHeight(CapsuleHalfHeightSize);
	CapsuleCollider->SetCapsuleRadius(CapsuleRadiusSize);

	// Sets up the camera and attaches it to the capsule
	CameraComponent->SetupAttachment(CapsuleCollider);
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->SetRelativeLocation(CameraSpawnLocation);

	TowerPreviewLocation->SetupAttachment(CapsuleCollider);

	MovementComponent->bOrientRotationToMovement = false;

	// Sets up the player arms mesh
	ArmsMesh->SetupAttachment(CameraComponent);
	ArmsMesh->SetRelativeTransform(ArmsMeshTransform);

	// Sets Up Gun Postion Mesh (A visiual representation of where the player's gun will be)
	GunPositionMesh->SetupAttachment(ArmsMesh, FName(TEXT("hand_rGrip")));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GunPositionMeshFinder(TEXT("/Game/MilitaryWeapSilver/Weapons/Shotgun_A"));
	if (GunPositionMeshFinder.Succeeded())
	{
		GunPositionMesh->SetSkeletalMesh(GunPositionMeshFinder.Object);
		GunPositionMesh->SetRelativeTransform(GunPositonMeshTransform);
		// Sets the mesh to be hidden in game (its only used in the viewport to test the position of gun models being held)
		GunPositionMesh->bHiddenInGame = true;
		UE_LOG(LogTemp, Warning, TEXT("Static mesh successfully set for C_Player: GunPositionMesh"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to set static mesh for C_Player: GunPositionMesh"));
	}
}

// Called to bind functionality to input
void AC_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Sets the chaaracter to allow looking around (left/right/up/down)
	// Allows the player to still move when looking up/ down
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Mouse Movement Inputs 
	// "Text" is the input name in the project settings, &AC_Player::Function is the function to be called upon input
	// MAYBE: move to player controller (although the original project did not have a PC)
	PlayerInputComponent->BindAxis("Look Left / Right", this, &AC_Player::LookLeftRight);
	PlayerInputComponent->BindAxis("Look Up / Down", this, &AC_Player::LookUpDown);
	PlayerInputComponent->BindAxis("Look Up / Down", this, &AC_Player::LookUpDown);

	// IE = Input Event
	PlayerInputComponent->BindAction("SkipCountdown", IE_Pressed, this, &AC_Player::SkipCountdown);
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AC_Player::PerformPrimaryActionPressed);
	PlayerInputComponent->BindAction("PrimaryAction", IE_Released, this, &AC_Player::PerformPrimaryActionReleased);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AC_Player::ReloadGun);

	// Keyboard Movement Inputs
	PlayerInputComponent->BindAxis("Move Forward / Backwards", this, &AC_Player::MoveForwardBackwards);
	PlayerInputComponent->BindAxis("Move Left / Right", this, &AC_Player::MoveLeftRight);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AC_Player::StartPerformSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AC_Player::EndPerformSprint);

	PlayerInputComponent->BindAction("PerformJump", IE_Pressed, this, &AC_Player::PerformJump);

	PlayerInputComponent->BindAction("PauseGame", IE_Pressed, this, &AC_Player::PauseGameActionPressed).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("ToggleStore", IE_Pressed, this, &AC_Player::ToggleStoreActionPressed);
}

// Spawns and attaches the gun to the player character
void AC_Player::Initialise(TSubclassOf<class AA_Gun> GunSpawnClass)
{
	GunSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Spawns the gun in the same posiiton as the gun position mesh
	Gun = GetWorld()->SpawnActor<AA_Gun>(GunSpawnClass, GunPositionMesh->GetComponentLocation(), GunPositionMesh->GetComponentRotation(), GunSpawnParameters);

	// Attaches the gun to the character
	if (Gun)
	{
		Gun->AttachToComponent(ArmsMesh, FAttachmentTransformRules::KeepWorldTransform, FName(TEXT("hand_rGrip")));
	}

	Gun->Initialise(CameraComponent);

	SetUpAnimInstanceType();
	AnimInst = Cast<UAnimInst_Player_Base>(ArmsMesh->GetAnimInstance());

	// Binds events to gun delegates
	Gun->OnShotFired.AddDynamic(this, &AC_Player::OnGunShotFired);
	Gun->OnShotFinished.AddDynamic(this, &AC_Player::StopArmsShootAnimation);
	Gun->OnRequestReload.AddDynamic(this, &AC_Player::ReloadGun);
	Gun->OnReloadFinished.AddDynamic(this, &AC_Player::OnGunReloadFinished);

	AnimInst->OnReloadFinishedAnimInst.AddDynamic(Gun, &AA_Gun::FinishReloading);
}

// Shoots the gun / places tower
void AC_Player::PerformPrimaryActionPressed()
{
	if (!IsDead && !CurrentlyShooting)
	{
		if (CurrentlyHoldingTower)
		{
			RequestPlaceTower.Broadcast();
		}
		else
		{
			CurrentlyShooting = true;
			Gun->StartShoting();

			GetWorldTimerManager().SetTimer(TH_Shooting, this, &AC_Player::ResetShooting, Gun->RateOfFire, false);
		}
	}
}

void AC_Player::PerformPrimaryActionReleased()
{
	Gun->EndShooting();
}

void AC_Player::SkipCountdown()
{
	RequestSkipCountdown.Broadcast();
}

void AC_Player::PauseGameActionPressed()
{
	RequestPauseGame.Broadcast(!UGameplayStatics::IsGamePaused(GetWorld()));
}

void AC_Player::ToggleStoreActionPressed()
{
	if(!IsDead)
	{
		RequestToggleStore.Broadcast();
	}
}

void AC_Player::TakeDamageCharacter(float DamageAmount)
{
	UGameplayStatics::SpawnSoundAttached(DamageRecievedSound, ArmsMesh);
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	OnDamageTaken.Broadcast(CurrentHealth, MaxHealth);

	if (CurrentHealth == 0.0f)
	{
		OnDead.Broadcast();
		if (CurrentlyHoldingTower)
		{
			RequestToggleStore.Broadcast();
		}
	}
}



// Gun Functions

// Changes the players blueprint animation class and gun spawn transform based on the gun class being used
void AC_Player::SetUpAnimInstanceType()
{
	switch (Gun->WeaponType)
	{
	case EWeaponType::AssaultRifle:
		SetUpAnimInst(AnimInstClassAssaultRifle, AssaultRifleTransform);
		break;
	case EWeaponType::Shotgun:
		SetUpAnimInst(AnimInstClassShotgun, ShotgunTransform);
		break;
	default:
		SetUpAnimInst(AnimInstClassBase, GunTransform);
		break;
	}
}

void AC_Player::SetUpAnimInst(TSubclassOf<class UAnimInst_Player_Base> AnimInstRef, FTransform GunTranformRef)
{
	ArmsMesh->SetAnimInstanceClass(AnimInstRef);
	GunTransform = GunTranformRef;
	GunPositionMesh->SetRelativeTransform(GunTransform);
}

void AC_Player::OnGunShotFired()
{
	AnimInst->CurrentlyShooting = true;
	CallOnAmmoAmountChangedED();
}

void AC_Player::ResetShooting()
{
	CurrentlyShooting = false;
}

void AC_Player::StopArmsShootAnimation()
{
	AnimInst->CurrentlyShooting = false;
}

void AC_Player::CallOnAmmoAmountChangedED()
{
	OnAmmoAmountChanged.Broadcast(Gun->MaxAmmo, Gun->CurrentAmmo);
}

void AC_Player::ReloadGun()
{
	// If the gun isnt currently being reloaded and the gun hasnt got a full magazine, reload it
	if (!Gun->CurrentlyReloading && Gun->CurrentAmmo != Gun->MaxAmmo)
	{
		AnimInst->CurrentlyReloading = true;
		Gun->StartReloading();
	}
}

void AC_Player::OnGunReloadFinished()
{
	CallOnAmmoAmountChangedED();
}


void AC_Player::SetCurrentlyHoldingTower(bool HoldingTower)
{
	CurrentlyHoldingTower = HoldingTower;
}


// Movement Functions

void AC_Player::LookLeftRight(float AxisValue)
{
	if (!IsDead)
	{
		AddControllerYawInput(AxisValue * MouseSensitivity);
	}
}

void AC_Player::LookUpDown(float AxisValue)
{
	if (!IsDead)
	{
		AddControllerPitchInput(AxisValue * MouseSensitivity);
	}
}

void AC_Player::MoveForwardBackwards(float AxisValue)
{
	ForwardWalkAmount = AxisValue;

	if (!IsDead)
	{
		this->AddMovementInput(this->GetActorForwardVector(), AxisValue);
		// If the player isnt moving forward, stop sprinting
		if (ForwardWalkAmount < 0)
		{
			SetSprint(false);
		}
	}
}

void AC_Player::MoveLeftRight(float AxisValue)
{
	if (!IsDead)
	{
		this->AddMovementInput(this->GetActorRightVector(), AxisValue);
	}
}

void AC_Player::SetSprint(bool Sprint)
{
	if (Sprint)
	{
		MovementComponent->MaxWalkSpeed = SprintSpeed;
		MovementComponent->MaxAcceleration = SprintAcceleration;
	}
	else
	{
		MovementComponent->MaxWalkSpeed = WalkSpeed;
		MovementComponent->MaxAcceleration = WalkAcceleration;
	}
}

void AC_Player::StartPerformSprint()
{
	if (ForwardWalkAmount > 0.0f)
	{
		SetSprint(true);
	}
}

void AC_Player::EndPerformSprint()
{
	SetSprint(false);
}

void AC_Player::PerformJump()
{
	if (!IsDead)
	{
		this->Jump();
	}
}

bool AC_Player::GetIsDead()
{
	return IsDead;
}