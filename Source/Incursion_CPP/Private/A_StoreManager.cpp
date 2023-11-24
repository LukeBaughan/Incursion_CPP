
#include "A_StoreManager.h"

#include "A_EnemySpawn.h"
#include "A_EndGoal.h"
#include "I_GridNode.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"

AA_StoreManager::AA_StoreManager() :
	UI_Manager(nullptr),
	Points(4000),
	NewWavePointsAwarded(100),
	TowerPreviewLocationComponent(nullptr),
	PreviewTower(nullptr),
	PreviewTowerClass(NULL),
	PlayerHoldingTower(false),
	TowerOccupyingGridNodeBelow(nullptr)
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
			PreviewTower->PlayerTowerPreviewLocationComponent = TowerPreviewLocationComponent;
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
		ExecutePlaceTowerSequence();
	}
	else if (CheckIfPlacedOnNode() && !CheckIfTowerBlocksPath())
	{
		II_GridNode* GridNodeInterface = Cast<II_GridNode>(GetGridNodeBelowTowerPreview());

		if (GridNodeInterface)
		{
			TowerOccupyingGridNodeBelow = GridNodeInterface->GetOccupyingTower();

			if (IsValid(TowerOccupyingGridNodeBelow))
			{
				if (CheckCanReplaceOccupyingTower())
				{

					// Towers are sold for half of their original price
					AddPoints(TowerOccupyingGridNodeBelow->Cost / 2);
					TowerOccupyingGridNodeBelow->Destroy();
					ExecutePlaceTowerSequence();
				}
				else
				{
					UI_Manager->DisplayCantBuildWidget();
				}
			}
			else
			{
				UI_Manager->DisplayCantBuildWidget();
			}
		}
		else
		{
			UI_Manager->DisplayCantBuildWidget();
		}
	}
	else
	{
		UI_Manager->DisplayCantBuildWidget();
	}
}

AActor* AA_StoreManager::GetGridNodeBelowTowerPreview()
{
	FVector TowerPreviewLocation = PreviewTower->BaseSceneComponent->GetComponentLocation();
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
	return IsValid(GetGridNodeBelowTowerPreview());
}

bool AA_StoreManager::CheckIfNodeOccupied()
{
	II_GridNode* GridNodeInterface = Cast<II_GridNode>(GetGridNodeBelowTowerPreview());

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
bool AA_StoreManager::CheckIfTowerBlocksPath()
{
	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	UNavigationPath* NavigationPath = NavigationSystem->FindPathToLocationSynchronously(GetWorld(), EnemySpawnLocation, EndGoalLocation);

	// If the path lengh is smaller than the distance between the two points, then the path must be blocked
	// When trying to block the path with towers diagonally, there is still a partial path so it must also be checked
	if (NavigationPath->GetPathLength() < FVector::Dist(EnemySpawnLocation, EndGoalLocation) || NavigationPath->IsPartial())
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Checks if the player is trying to build a non-blockade tower on a blockade tower or if the tower is a sell tower
bool AA_StoreManager::CheckCanReplaceOccupyingTower()
{
	FString PreviewTowerName = PreviewTower->GetName();

	return (TowerOccupyingGridNodeBelow->GetName().Contains("Blockade") && !PreviewTowerName.Contains("Blockade")
		|| PreviewTowerName.Contains("Sell"));
}

void AA_StoreManager::ExecutePlaceTowerSequence()
{
	// If a sell tower is being placed, make the node unoccupied
	bool OccupyGridNode = !PreviewTower->GetName().Contains("Sell");
	II_GridNode* GridNodeInterface = Cast<II_GridNode>(GetGridNodeBelowTowerPreview());

	if (GridNodeInterface)
	{
		GridNodeInterface->SetOccupied(OccupyGridNode, PreviewTower);
	}
	PlaceTower();
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