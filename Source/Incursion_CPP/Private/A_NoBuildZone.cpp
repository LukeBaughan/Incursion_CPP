
#include "A_NoBuildZone.h"

#include "A_GridNode.h"
#include "I_GridNode.h"

AA_NoBuildZone::AA_NoBuildZone() :
	BoxCollider(CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider")))
{
	BoxCollider->SetupAttachment(GetRootComponent());
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	BoxCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}
void AA_NoBuildZone::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OverlappingGridNodes;

	BoxCollider->GetOverlappingActors(OverlappingGridNodes, AA_GridNode::StaticClass());

	II_GridNode* GridNodeInterface;

	for (AActor* GridNode : OverlappingGridNodes)
	{
		FString GridNodeName = GridNode->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("%s"), *GridNodeName));
		GridNodeInterface = Cast<II_GridNode>(GridNode);

		if (GridNodeInterface)
		{
			GridNodeInterface->SetOccupied(true, nullptr);
		}
	}
}
