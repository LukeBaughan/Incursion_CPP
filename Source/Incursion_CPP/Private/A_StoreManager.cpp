
#include "A_StoreManager.h"

AA_StoreManager::AA_StoreManager() :
	UI_Manager(nullptr),
	Points(400),
	NewWavePointsAwarded(100),
	TowerPreviewLocation(nullptr),
	PreviewTower(nullptr),
	PreviewTowerClass(NULL),
	PlayerHoldingTower(false)
{

}

void AA_StoreManager::Initialise(AA_UI_Manager* UI_ManagerRef, USceneComponent* TowerPreviewLocationRef)
{
	TowerPreviewLocation = TowerPreviewLocationRef;

	UI_Manager = UI_ManagerRef;
	UI_Manager->WidgetHUD->WidgetPoints->SetPoints(Points);
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
			PreviewTower->SetActorLocation(TowerPreviewLocation->GetComponentLocation());
			PreviewTower->AttachToComponent(TowerPreviewLocation, FAttachmentTransformRules::SnapToTargetIncludingScale);
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

void AA_StoreManager::CheckCanPlaceTower()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("AA_StoreManager::CheckCanPlaceTower")));
}