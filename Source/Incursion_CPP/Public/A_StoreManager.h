
#pragma once

#include "CoreMinimal.h"

#include "A_Tower.h"
#include "A_UI_Manager.h"
#include "GameFramework/Actor.h"

#include "A_StoreManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStoreManager_OnRequestSetPlayerHoldingTower, bool, HoldingTower);

UCLASS()
class INCURSION_CPP_API AA_StoreManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AA_StoreManager();

	void Initialise(AA_UI_Manager* UI_ManagerRef, USceneComponent* TowerPreviewLocationRef);

	UFUNCTION()
		void AddPoints(int Amount);

	UFUNCTION()
		void AddNewWavePoints();

	UFUNCTION()
		void ToggleStoreUI();

	UFUNCTION()
		void CheckCanPurchaseTower(TSubclassOf<class AA_Tower> TowerClass);

	UFUNCTION()
		void CheckCanPlaceTower();

	FStoreManager_OnRequestSetPlayerHoldingTower OnRequestSetPlayerHoldingTower;

	USceneComponent* TowerPreviewLocationComponent;

private:

	AActor* GetGridNodeBelowTowerPreview(AA_Tower* TowerPreview);
	bool CheckIfPlacedOnNode();
	bool CheckIfNodeOccupied();
	bool CheckIfTowerBlocksPath();
	void PlaceTower();

	AA_UI_Manager* UI_Manager;

	AA_Tower* PreviewTower;
	TSubclassOf<class AA_Tower> PreviewTowerClass;

	FVector EnemySpawnLocation;
	FVector EndGoalLocation;

	int Points;
	int NewWavePointsAwarded;
	bool PlayerHoldingTower;
};
