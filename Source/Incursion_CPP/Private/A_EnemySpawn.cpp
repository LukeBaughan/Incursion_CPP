
#include "A_EnemySpawn.h"

// Sets default values
AA_EnemySpawn::AA_EnemySpawn() :
	BoxCollider(CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider")))
{
	BoxCollider->SetupAttachment(RootComponent);
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}