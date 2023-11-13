
#include "A_Tower.h"

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

	EnemyCollider(CreateDefaultSubobject<UBoxComponent>(TEXT("Enemy Collider"))),

	Damage(1.0f),
	RateOfFire(1.0f),
	Range(10.0f),
	Cost(100),

	PreviewMode(true)
{
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

	EnemyCollider->SetupAttachment(TowerSceneComponent);
	EnemyCollider->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));

	EnemyCollider->bDynamicObstacle = true;
	// ECC_GameTraceChannel4 = Turret Collision Channel
	EnemyCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	EnemyCollider->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel4);
	EnemyCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// ECC_GameTraceChannel2 = Enemy Collision Channel
	EnemyCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);

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
		EnemyCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		EnemyCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
		EnemyCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		Wall->SetVisibility(false);
	}
}

void AA_Tower::OnPlaced()
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
				TowerInterface->ShowWalls(TowerSceneComponent->GetComponentLocation());
			}
		}
	}
}

// Towers with more than one muzzle should override this
void AA_Tower::GetAllMuzzles()
{
	AllMuzzles.Add(MuzzlesSceneComponent);
	AllShootLocations.Add(ShootLocationSceneComponent);
}

void AA_Tower::ShowWalls(FVector PlacedTowerPosition)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("AA_Tower::ShowWalls")));
}