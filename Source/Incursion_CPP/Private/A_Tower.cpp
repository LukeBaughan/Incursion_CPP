
#include "A_Tower.h"

#include "I_Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "C_Enemy.h"

AA_Tower::AA_Tower() :
	TowerSceneComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Tower"))),
	BaseSceneComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Base"))),
	BaseMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"))),

	WallsSceneComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Walls"))),
	WallFront(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Front"))),
	WallBack(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Back"))),
	WallLeft(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Left"))),
	WallRight(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Right"))),
	WallBackLeft(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Back Left"))),
	WallBackRight(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Back Right"))),
	WallFrontLeft(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Front Left"))),
	WallFrontRight(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Front Right"))),

	BodySceneComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Body"))),
	BodyMeshLower(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Lower"))),
	BodyMeshUpper(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Upper"))),
	ArrowComponent(CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"))),

	TurretSceneComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Turret"))),
	TurretMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"))),

	MuzzlesSceneComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Muzzles"))),
	MuzzleMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Muzzle Mesh"))),

	ShootLocationSceneComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Shoot Location"))),

	EnemyColliderMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Collider Mesh"))),
	AttackCollider(CreateDefaultSubobject<USphereComponent>(TEXT("Attack Collider"))),

	CurrentMuzzleIndex(0),
	NumberOfMuzzles(1),
	CurrentMuzzle(nullptr),
	CurrentMuzzleStartLocation(FVector::ZeroVector),
	CurrentShootLocation(nullptr),
	ShootSound(nullptr),
	ShootFX(nullptr),
	ShootWorldLocation(FVector::ZeroVector),
	TargetWorldLocation(FVector::ZeroVector),

	Damage(1.0f),
	RateOfFire(1.0f),
	Range(500.0f),
	Cost(100),

	PreviewMode(true),
	PreviewZ_Position(30.0f),
	PlayerTowerPreviewLocationComponent(nullptr),
	PlayerTowerPreviewLocation(FVector::ZeroVector),

	TimelineLookAtEnemy(CreateDefaultSubobject<UTimelineComponent>(TEXT("Look At Enemy Timeline"))),
	fCurveLookAtEnemy(nullptr),

	TimelineBarrelRecoil(CreateDefaultSubobject<UTimelineComponent>(TEXT("Apply Barrel Recoil Timeline"))),
	fCurveBarrelRecoil(nullptr),
	MuzzleRecoilDisplacement(30.0f),

	SellTowerClass(nullptr),

	PelletAmount(0),
	PelletMaxOffset(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	TowerSceneComponent->SetupAttachment(RootComponent);
	BaseSceneComponent->SetupAttachment(TowerSceneComponent);
	BaseMesh->SetupAttachment(BaseSceneComponent);

	WallsSceneComponent->SetupAttachment(TowerSceneComponent);
	WallBack->SetupAttachment(WallsSceneComponent);
	WallFront->SetupAttachment(WallsSceneComponent);
	WallLeft->SetupAttachment(WallsSceneComponent);
	WallRight->SetupAttachment(WallsSceneComponent);
	WallBackLeft->SetupAttachment(WallsSceneComponent);
	WallBackRight->SetupAttachment(WallsSceneComponent);
	WallFrontLeft->SetupAttachment(WallsSceneComponent);
	WallFrontRight->SetupAttachment(WallsSceneComponent);

	BodySceneComponent->SetupAttachment(BaseSceneComponent);
	BodyMeshLower->SetupAttachment(BodySceneComponent);
	BodyMeshUpper->SetupAttachment(BodySceneComponent);
	ArrowComponent->SetupAttachment(BodySceneComponent);
	ArrowComponent->ArrowSize = 2.0f;

	TurretSceneComponent->SetupAttachment(BodySceneComponent);
	TurretMesh->SetupAttachment(TurretSceneComponent);

	MuzzlesSceneComponent->SetupAttachment(TurretSceneComponent);

	MuzzleMesh->SetupAttachment(MuzzlesSceneComponent);
	ShootLocationSceneComponent->SetupAttachment(MuzzleMesh);

	EnemyColliderMesh->SetupAttachment(TowerSceneComponent);

	EnemyColliderMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// ECC_GameTraceChannel4 = Turret Collision Channel
	EnemyColliderMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel4);
	EnemyColliderMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// ECC_GameTraceChannel2 = Enemy Collision Channel
	EnemyColliderMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);


	AttackCollider->SetupAttachment(TowerSceneComponent);
	AttackCollider->SetSphereRadius(Range);
	AttackCollider->bHiddenInGame = false;

	AttackCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	AttackCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// ECC_GameTraceChannel2 = Enemy Collision Channel
	AttackCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);

	AllWalls.Add(WallFront);
	AllWalls.Add(WallBack);
	AllWalls.Add(WallLeft);
	AllWalls.Add(WallRight);
	AllWalls.Add(WallFrontLeft);
	AllWalls.Add(WallFrontRight);
	AllWalls.Add(WallBackLeft);
	AllWalls.Add(WallBackRight);

	for (UStaticMeshComponent* Wall : AllWalls)
	{
		EnemyColliderMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		EnemyColliderMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
		EnemyColliderMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		Wall->SetVisibility(false);
	}

	static ConstructorHelpers::FObjectFinder<UCurveFloat> fCurveLookAtEnemyOF(TEXT("/Game/Luke/Tower/Curve_LookAtEnemy"));
	if (fCurveLookAtEnemyOF.Succeeded())
	{
		fCurveLookAtEnemy = fCurveLookAtEnemyOF.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("A_Tower: Unable to set fCurveLookAtEnemy"));
	}

	static ConstructorHelpers::FObjectFinder<UCurveFloat> fCurveBarrelRecoilOF(TEXT("/Game/Luke/Tower/Curve_ApplyBarrelRecoil"));
	if (fCurveBarrelRecoilOF.Succeeded())
	{
		fCurveBarrelRecoil = fCurveBarrelRecoilOF.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("A_Tower: Unable to set fCurveBarrelRecoil"));
	}
}

void AA_Tower::BeginPlay()
{
	Super::BeginPlay();

	AttackCollider->OnComponentBeginOverlap.AddDynamic(this, &AA_Tower::AttackColliderOnOverlapBegin);
	AttackCollider->OnComponentEndOverlap.AddDynamic(this, &AA_Tower::AttackColliderOnOverlapEnd);

	LookAtEnemyTrack.BindDynamic(this, &AA_Tower::LookAtEnemyTimelineFunction);

	if (fCurveLookAtEnemy)
	{
		TimelineLookAtEnemy->AddInterpFloat(fCurveLookAtEnemy, LookAtEnemyTrack);
	}

	BarrelRecoilTrack.BindDynamic(this, &AA_Tower::ApplyBarrelRecoilTimelineFunction);

	if (fCurveBarrelRecoil)
	{
		TimelineBarrelRecoil->AddInterpFloat(fCurveBarrelRecoil, BarrelRecoilTrack);
	}
}
void AA_Tower::Tick(float DeltaTime)
{
	if (PreviewMode)
	{
		if (IsValid(PlayerTowerPreviewLocationComponent))
		{
			PlayerTowerPreviewLocation = PlayerTowerPreviewLocationComponent->GetComponentLocation();
			this->SetActorLocation(FVector(FMath::GridSnap(PlayerTowerPreviewLocation.X, 200.0f),
				FMath::GridSnap(PlayerTowerPreviewLocation.Y, 200.0f), PreviewZ_Position));
			this->SetActorRotation(FRotator::ZeroRotator);
		}
	}
}

void AA_Tower::OnPlaced_Implementation()
{
	GetAllMuzzles();

	for (USceneComponent* Muzzle : AllMuzzles)
	{
		AllMuzzleStartLocations.Add(Muzzle->GetRelativeLocation());
	}

	PreviewMode = false;

	TArray<AActor*> OverlappingTowers;
	II_Tower* TowerInterface;

	// Calls the ShowWalls function on nearby towers (collided with an invisible wall)
	for (UStaticMeshComponent* Wall : AllWalls)
	{
		GetOverlappingActors(OverlappingTowers, AA_Tower::StaticClass());
		for (AActor* Tower : OverlappingTowers)
		{
			TowerInterface = Cast<II_Tower>(Tower);

			if (TowerInterface)
			{
				TowerInterface->Execute_ShowWalls(Tower, TowerSceneComponent->GetComponentLocation());
			}
		}
	}
}

// Hides all walls connected to the previous tower(before sold)
void AA_Tower::OnPlacedSellOverride()
{
	TArray<UPrimitiveComponent*> OverlappingComponents;
	BaseMesh->GetOverlappingComponents(OverlappingComponents);

	for (UPrimitiveComponent* Component : OverlappingComponents)
	{
		if (UKismetMathLibrary::ClassIsChildOf(Component->GetOwner()->GetClass(), AA_Tower::StaticClass()) && Component->GetName().Contains("Wall"))
		{
			Component->SetVisibility(false);
			Component->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			Component->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
		}
	}

	Destroy();
}

// Towers with more than one muzzle should override this
void AA_Tower::GetAllMuzzles_Implementation()
{
	AllMuzzles.Add(MuzzlesSceneComponent);
	AllShootLocations.Add(ShootLocationSceneComponent);
}

// Shows a wall based on which side the placed tower is
void AA_Tower::ShowWalls_Implementation(FVector PlacedTowerPosition)
{
	FVector ThisTowerPosition = TowerSceneComponent->GetComponentLocation();
	if (PlacedTowerPosition != ThisTowerPosition)
	{
		if ((PlacedTowerPosition.X - ThisTowerPosition.X) > 0.0f)
		{
			if ((PlacedTowerPosition.Y - ThisTowerPosition.Y) == 0.0f)
			{
				ShowWall(WallFront);
			}
			else
			{
				if ((PlacedTowerPosition.Y - ThisTowerPosition.Y) < 0.0f)
				{
					ShowWall(WallFrontLeft);
				}
				else
				{
					ShowWall(WallFrontRight);
				}
			}
		}
		else
		{
			if ((PlacedTowerPosition.X - ThisTowerPosition.X) == 0.0f)
			{
				if ((PlacedTowerPosition.Y - ThisTowerPosition.Y) > 0.0f)
				{
					ShowWall(WallRight);
				}
				else
				{
					ShowWall(WallLeft);
				}
			}
			else
			{
				if ((PlacedTowerPosition.Y - ThisTowerPosition.Y) == 0.0f)
				{
					ShowWall(WallBack);
				}
				else
				{
					if ((PlacedTowerPosition.Y - ThisTowerPosition.Y) < 0.0f)
					{
						ShowWall(WallBackLeft);
					}
					else
					{
						ShowWall(WallBackRight);
					}
				}
			}
		}
	}
}

void AA_Tower::ShowWall(UStaticMeshComponent* Wall)
{
	Wall->SetVisibility(true);
	// ECC_GameTraceChannel3 = Player Collision Channel
	Wall->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
}

void AA_Tower::AttackColliderOnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// The actor is added to an array of targets if it is an enemy and is not dead
	II_Character* CharacterInterface = Cast<II_Character>(OtherActor);

	if (CharacterInterface)
	{
		II_Enemy* EnemyInterface = Cast<II_Enemy>(OtherActor);

		if (!CharacterInterface->GetIsDead() && EnemyInterface)
		{
			TargetsArray.Add(OtherActor);

			if (!PreviewMode)
			{
				// Shoots at the first target in the array
				LookAtEnemy();
				GetWorldTimerManager().SetTimer(TH_ShootTarget, this, &AA_Tower::ShootTarget, RateOfFire, true);
			}
		}
	}
}

void AA_Tower::LookAtEnemy()
{
	TimelineLookAtEnemy->PlayFromStart();
}

void AA_Tower::LookAtEnemyTimelineFunction(float Alpha)
{
	if (TargetsArray.Num() > 0)
	{
		if (IsValid(TargetsArray[0]))
		{
			AActor* CurrentTarget = TargetsArray[0];

			if (IsValid(CurrentTarget->GetRootComponent()))
			{
				FVector TargetLocation = CurrentTarget->GetRootComponent()->GetComponentLocation();

				// Rotates Body
				BodySceneComponent->SetWorldRotation(FRotator(0.0f, FMath::Lerp(BodySceneComponent->GetComponentRotation().Yaw,
					UKismetMathLibrary::FindLookAtRotation(BodySceneComponent->GetComponentLocation(), TargetLocation).Yaw, Alpha), 0.0f));

				// Rotates Turret
				FRotator TurretWorldRotation = TurretSceneComponent->GetComponentRotation();

				TurretSceneComponent->SetWorldRotation(FRotator(FMath::Lerp(TurretWorldRotation.Pitch,
					UKismetMathLibrary::FindLookAtRotation(TurretSceneComponent->GetComponentLocation(), TargetLocation).Pitch, Alpha),
					TurretWorldRotation.Yaw, TurretWorldRotation.Roll));
			}
			else
			{
				RemoveFirstEnemyFromTargets();
			}
		}
		else
		{
			RemoveFirstEnemyFromTargets();
		}
	}
}

// If the target is dead or invalid, remove them from the targets array, otherwise, look at and shoot the target
void AA_Tower::ShootTarget()
{
	if (TargetsArray.Num() > 0)
	{
		if (IsValid(TargetsArray[0]))
		{
			II_Character* CharacterInterface = Cast<II_Character>(TargetsArray[0]);

			if (CharacterInterface)
			{
				if (CharacterInterface->GetIsDead())
				{
					RemoveFirstEnemyFromTargets();
				}
				else
				{
					if (!PreviewMode)
					{
						LookAtEnemy();
						GetMuzzleToShoot();

						TargetWorldLocation = TargetsArray[0]->GetActorLocation();
						ShootWorldLocation = CurrentShootLocation->GetComponentLocation();
						ExecuteLineTraceShoot();
						// Spawns a muzzle flash FX
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShootFX, ShootWorldLocation,
							UKismetMathLibrary::FindLookAtRotation(ShootWorldLocation, TargetWorldLocation));
						// Moves the barrel back (recoil)
						TimelineBarrelRecoil->PlayFromStart();
					}
				}
			}
		}
		else
		{
			RemoveFirstEnemyFromTargets();
		}
	}

}

// OVERRIDE IF YOU WANT TO CHANGE THE WAY THE TOWER SHOOTS (I.E SHOTGUN PELLET SPREAD)
void AA_Tower::ExecuteLineTraceShoot_Implementation()
{
	// Plays sound and performs line trace
	BFL_Incursion->LineTraceShootEnemy(GetWorld(), ShootWorldLocation, TargetWorldLocation, Damage, ShootSound);
}

// Shoots multiple line traces in random directions (using filtered randomness)
void AA_Tower::ExecuteLineTraceShootShotgun()
{
	for (int PelletIndex = 0; PelletIndex < PelletAmount; ++PelletIndex)
	{
		TargetWorldLocation = FVector(TargetWorldLocation.X + BFL_Incursion->GetAveragePelletOffset(PelletMaxOffset),
			TargetWorldLocation.Y + BFL_Incursion->GetAveragePelletOffset(PelletMaxOffset),
			TargetWorldLocation.Z + BFL_Incursion->GetAveragePelletOffset(PelletMaxOffset));

		// Only plays a sound effect for one pellet firing
		if (PelletIndex != 0)
		{
			BFL_Incursion->LineTraceShootEnemy(GetWorld(), ShootWorldLocation, TargetWorldLocation, Damage, ShootSound);
		}
		else
		{
			BFL_Incursion->LineTraceShootEnemy(GetWorld(), ShootWorldLocation, TargetWorldLocation, Damage, ShootSound);
		}
	}
}

void AA_Tower::RemoveFirstEnemyFromTargets()
{
	TargetsArray.RemoveAt(0);

	// If the targets list is empty, stop shooting
	if (TargetsArray.Num() != 0)
	{
		LookAtEnemy();
	}
}

// Cylces through which muzzle to shoot from (if theres more than one muzzle)
void AA_Tower::GetMuzzleToShoot()
{
	CurrentMuzzle = AllMuzzles[CurrentMuzzleIndex];
	CurrentMuzzleStartLocation = AllMuzzleStartLocations[CurrentMuzzleIndex];
	CurrentShootLocation = AllShootLocations[CurrentMuzzleIndex];

	if (CurrentMuzzleIndex < NumberOfMuzzles - 1)
	{
		++CurrentMuzzleIndex;
	}
	else
	{
		CurrentMuzzleIndex = 0;
	}
}

void AA_Tower::ApplyBarrelRecoilTimelineFunction(float Alpha)
{
	FVector CurrentMuzzleLocation = CurrentMuzzle->GetRelativeLocation();

	CurrentMuzzle->SetRelativeLocation(FMath::Lerp(CurrentMuzzleStartLocation,
		FVector(FMath::Clamp(CurrentMuzzleLocation.X - MuzzleRecoilDisplacement, CurrentMuzzleStartLocation.X -
			MuzzleRecoilDisplacement, CurrentMuzzleStartLocation.X), CurrentMuzzleLocation.Y, CurrentMuzzleLocation.Z), Alpha));
}

// Removes enemies when they leave the radius
void AA_Tower::AttackColliderOnOverlapEnd_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("AA_Tower::AttackColliderOnOverlapEnd")));

	II_Character* CharacterInterface = Cast<II_Character>(OtherActor);

	if (CharacterInterface)
	{
		if (!CharacterInterface->GetIsDead())
		{
			TargetsArray.Remove(OtherActor);

			if (TargetsArray.Num() != 0)
			{
				LookAtEnemy();
			}
		}
	}
}