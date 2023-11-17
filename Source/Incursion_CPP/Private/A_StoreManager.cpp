
#include "A_StoreManager.h"

#include "A_EnemySpawn.h"
#include "A_EndGoal.h"
#include "I_GridNode.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

AA_StoreManager::AA_StoreManager() :
	UI_Manager(nullptr),
	Points(4000),
	NewWavePointsAwarded(100),
	TowerPreviewLocationComponent(nullptr),
	PreviewTower(nullptr),
	PreviewTowerClass(NULL),
	PlayerHoldingTower(false)
{

}

void AA_StoreManager::Initialise(AA_UI_Manager* UI_ManagerRef, USceneComponent* TowerPreviewLocationRef)
{
	TowerPreviewLocationComponent = TowerPreviewLocationRef;

	UI_Manager = UI_ManagerRef;
	UI_Manager->WidgetHUD->WidgetPoints->SetPoints(Points);

	EnemySpawnLocation = UGameplayStatics::GetActorOfClass(GetWorld(), AA_EnemySpawn::StaticClass())->GetActorLocation();
	EndGoalLocation = UGameplayStatics::GetActorOfClass(GetWorld(), AA_EndGoal::StaticClass())->GetActorLocation();
}

void AA_StoreManager::AddPoints(int Amount)
{
	Points += Amount;
	UI_Manager->WidgetHUD->WidgetPoints->SetPoints(Points);
}

void AA_StoreManager::AddNewWavePoints()
{
	AddPoints(NewWavePointsAwarded);
}

void AA_StoreManager::ToggleStoreUI()
{
	// Destroys the preview if the player closes the store
	if (PlayerHoldingTower)
	{
		PreviewTower->Destroy();
		PlayerHoldingTower = false;
		OnRequestSetPlayerHoldingTower.Broadcast(PlayerHoldingTower);
	}
	else
	{
		UI_Manager->ToggleMenu(UI_Manager->WidgetStoreMenu);
	}
}

void AA_StoreManager::CheckCanPurchaseTower(TSubclassOf<class AA_Tower> TowerClass)
{
	PreviewTowerClass = TowerClass;

	if (PreviewTowerClass)
	{
		PreviewTower = GetWorld()->SpawnActor<AA_Tower>(PreviewTowerClass, FVector(0.0f, 0.0f, -1500.0f), FRotator::ZeroRotator);
		// Checks if the player has enough points to purchase the tower
		if (Points >= PreviewTower->Cost && !PlayerHoldingTower)
		{
			PreviewTower->SetActorLocation(TowerPreviewLocationComponent->GetComponentLocation());
			PreviewTower->AttachToComponent(TowerPreviewLocationComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
			UI_Manager->ToggleMenu(UI_Manager->WidgetStoreMenu);

			PlayerHoldingTower = true;
			OnRequestSetPlayerHoldingTower.Broadcast(PlayerHoldingTower);
		}
		else
		{
			PreviewTower->Destroy();
		}
	}
}

// Only allows the tower to be placed if it is on an unoccupied tile and doesnt block the path for 
// the enemies(if the player tries to build on a blockade tower, replace it with the new tower)
void AA_StoreManager::CheckCanPlaceTower()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("AA_StoreManager::CheckCanPlaceTower")));

	if (CheckIfPlacedOnNode() && !CheckIfNodeOccupied() && !CheckIfTowerBlocksPath())
	{
		// If a sell tower is being placed, make the node unoccupied
		bool OccupyGridNode = !PreviewTower->GetName().Contains("Sell");
		II_GridNode* GridNodeInterface = Cast<II_GridNode>(GetGridNodeBelowTowerPreview(PreviewTower));

		if (GridNodeInterface)
		{
			GridNodeInterface->SetOccupied(OccupyGridNode, PreviewTower);
		}
		PlaceTower();
	}
	else
	{
		UI_Manager->DisplayCantBuildWidget();
	}
}

AActor* AA_StoreManager::GetGridNodeBelowTowerPreview(AA_Tower* TowerPreview)
{
	FVector TowerPreviewLocation = TowerPreview->BaseSceneComponent->GetComponentLocation();
	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionParameters;

	// ECC_GameTraceChannel5 = Grid Node Collision Object Channel
	CollisionParameters.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel5);

	bool LineTrace = GetWorld()->LineTraceSingleByObjectType(HitResult, TowerPreviewLocation,
		(TowerPreviewLocation + FVector(0.0f, 0.0f, -300.0f)), CollisionParameters);

	return HitResult.GetActor();
}

// Returns true if the tower preview collider is above a grid node
bool AA_StoreManager::CheckIfPlacedOnNode()
{
	return IsValid(GetGridNodeBelowTowerPreview(PreviewTower));
}

bool AA_StoreManager::CheckIfNodeOccupied()
{
	II_GridNode* GridNodeInterface = Cast<II_GridNode>(GetGridNodeBelowTowerPreview(PreviewTower));

	if (GridNodeInterface)
	{
		return GridNodeInterface->GetOccupied();
	}
	else
	{
		return false;
	}
}

// Returns true if the tower doesnt block the enemies path to the goal if placed
// POTENTIAL REASON FOR ISSUE: Always returns false because there needs to be a temp tower placed to block the path
// altough even when the path is fully blocked, the next tower can still be placed
bool AA_StoreManager::CheckIfTowerBlocksPath()
{
	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	ANavigationData* NavigationData = NavigationSystem->GetAbstractNavData();

	FPathFindingQuery PathFindingQuery(this, *NavigationData, EnemySpawnLocation, EndGoalLocation);
	PathFindingQuery.SetAllowPartialPaths(false);
	PathFindingQuery.NavAgentProperties.AgentRadius = 15000.0f;
	PathFindingQuery.NavAgentProperties.AgentStepHeight = 0.0f;
	int32 NumberOfVisitedNodes = 0;
	bool x = NavigationSystem->TestPathSync(PathFindingQuery, EPathFindingMode::Regular, &NumberOfVisitedNodes);

	DrawDebugLine(GetWorld(), EnemySpawnLocation, EndGoalLocation, FColor::Red, true, 1, 5.f);

	return NavigationSystem->TestPathSync(PathFindingQuery, EPathFindingMode::Regular, &NumberOfVisitedNodes);
}

// Detaches the tower from the player and snaps it to the nearest grid node
void AA_StoreManager::PlaceTower()
{
	PreviewTower->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	FVector TowerPreviewLocation = PreviewTower->GetRootComponent()->GetComponentLocation();
	// 200.0f = Grid Width
	PreviewTower->SetActorLocation(FVector(FMath::GridSnap(TowerPreviewLocation.X, 200.0f), FMath::GridSnap(TowerPreviewLocation.Y, 200.0f), 0.0f));
	PreviewTower->SetActorRotation(FRotator::ZeroRotator);

	PlayerHoldingTower = false;
	OnRequestSetPlayerHoldingTower.Broadcast(PlayerHoldingTower);

	PreviewTower->OnPlaced();
	AddPoints(PreviewTower->Cost * -1);
}