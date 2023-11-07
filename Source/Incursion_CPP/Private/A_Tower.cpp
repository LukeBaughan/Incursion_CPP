
#include "A_Tower.h"

AA_Tower::AA_Tower() :
	TowerSceneComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Tower"))),
	BaseSceneComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Base"))),
	BaseMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"))),

	Damage(1.0f),
	RateOfFire(1.0f),
	Range(10.0f),
	Cost(100)
{
	TowerSceneComponent->SetupAttachment(GetRootComponent());
	BaseSceneComponent->SetupAttachment(TowerSceneComponent);
	BaseMesh->SetupAttachment(BaseSceneComponent);
}