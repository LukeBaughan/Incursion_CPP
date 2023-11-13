
#include "A_GridNode.h"

AA_GridNode::AA_GridNode(): 
    PlaneMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Component")))
{
	PlaneMesh->SetupAttachment(RootComponent);
    PlaneMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    // ECC_GameTraceChannel5 = Gird Node Channel
    PlaneMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel5);
    PlaneMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
}

void AA_GridNode::SetOccupied(bool IsOccupied, AA_Tower* OccupyingTowerRef)
{
    Occupied = IsOccupied;
    OccupyingTower = OccupyingTowerRef;
}

bool AA_GridNode::GetOccupied()
{
    return Occupied;
}

AA_Tower* AA_GridNode::GetOccupyingTower()
{
    return OccupyingTower;
}
