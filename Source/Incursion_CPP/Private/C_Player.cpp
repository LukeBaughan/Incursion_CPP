// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Player.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AC_Player::AC_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sets the shape of the capsule collider
	CapsuleHalfHeightSize = 96.0f;
	CapsuleRadiusSize = 55.0f;

	GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleHalfHeightSize);
	GetCapsuleComponent()->SetCapsuleRadius(CapsuleRadiusSize);

	// Sets up the camera and attaches it to the capsule
	CameraSpawnLocation = FVector(-39.5f, 0.0f, 64.2f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->bUsePawnControlRotation = true;

	CameraComponent->SetRelativeLocation(CameraSpawnLocation);

	MovementComponent = GetCharacterMovement();
	MovementComponent->bOrientRotationToMovement = false;

	// Sets up the player arms mesh
	ArmsMeshTransform = FTransform(FRotator(1.73f, -80.15f, -6.0f), FVector(-5.33f, -15.25f, -164.54f), FVector::One());

	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms Mesh"));
	ArmsMesh->SetupAttachment(CameraComponent);
	ArmsMesh->SetRelativeTransform(ArmsMeshTransform);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmsMeshFinder(TEXT("/Game/FPS_Military_Arms/Mesh/SK_FPS_Military_Arm_Forest"));
	if (ArmsMeshFinder.Succeeded())
	{
		ArmsMesh->SetSkeletalMesh(ArmsMeshFinder.Object);
		UE_LOG(LogTemp, Warning, TEXT("Static mesh successfully set for C_Player: ArmsMesh"));
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Unable to set static mesh for C_Player: ArmsMesh"));

	// Sets Up Gun Postion Mesh (A visiual representation of where the player's gun will be)

	GunPositonMeshTransform = FTransform(FRotator(-2.5f, 265.8f, -358.5f), FVector(3.7f, 12.2f, -21.5f), FVector::One());

	Gun = NULL;
	GunPositionMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Position Mesh"));
	GunPositionMesh->SetupAttachment(CameraComponent);


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
		UE_LOG(LogTemp, Error, TEXT("Unable to set static mesh for C_Player: GunPositionMesh"));
}

// Called when the game starts or when spawned
void AC_Player::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->SetVisibility(true);
}

// Called every frame
void AC_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AC_Player::PerformPrimaryAction);

	// Keyboard Movement Inputs
	PlayerInputComponent->BindAxis("Move Forward / Backwards", this, &AC_Player::MoveForwardBackwards);
	PlayerInputComponent->BindAxis("Move Left / Right", this, &AC_Player::MoveLeftRight);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AC_Player::StartPerformSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AC_Player::EndPerformSprint);

	PlayerInputComponent->BindAction("PerformJump", IE_Pressed, this, &AC_Player::PerformJump);
}

// Called to bind functionality to input
void AC_Player::Initialise(TSubclassOf<class AA_Gun> GunSpawnClass)
{
	GunSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Spawns the gun in the same posiiton as the gun position mesh
	Gun = GetWorld()->SpawnActor<AA_Gun>(GunPositionMesh->GetComponentLocation(), GunPositionMesh->GetComponentRotation(), GunSpawnParameters);

	// Attaches the gun to the character
	if (Gun)
		Gun->AttachToComponent(CameraComponent, FAttachmentTransformRules::KeepWorldTransform); //NEED SOCKET NAME WHEN PLAYER MESH IS SET UP + CHANGE LOCATION FROM GUNPOS->CHARMESH

	Gun->Initialise(CameraComponent);
}

void AC_Player::PerformPrimaryAction()
{
	// TEMP: Shoots the gun
	Gun->ShootLineTrace();
}

void AC_Player::LookLeftRight(float AxisValue)
{
	if(!IsDead)
		AddControllerYawInput(AxisValue * MouseSensitivity);
}

void AC_Player::LookUpDown(float AxisValue)
{
	if(!IsDead)
		AddControllerPitchInput(AxisValue * MouseSensitivity);
}

void AC_Player::MoveForwardBackwards(float AxisValue)
{
	ForwardWalkAmount = AxisValue;

	if (!IsDead)
	{
		this->AddMovementInput(this->GetActorForwardVector(), AxisValue);
		// If the player isnt moving forward, stop sprinting
		if (ForwardWalkAmount < 0)
			SetSprint(false);
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
		SetSprint(true);
}

void AC_Player::EndPerformSprint()
{
	SetSprint(false);
}

void AC_Player::PerformJump()
{
	if(!IsDead)
		this->Jump();
}
