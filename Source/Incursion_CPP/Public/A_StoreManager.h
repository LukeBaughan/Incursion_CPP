
#pragma once

#include "CoreMinimal.h"

#include "A_Tower.h"
#include "A_UI_Manager.h"
#include "GameFramework/Actor.h"

#include "A_StoreManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStoreManager_OnRequestSetPlayerHoldingTower, bool, HoldingTower);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStoreManager_OnPointsAdded, int, Amount);

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
	FStoreManager_OnPointsAdded OnPointsAdded;

private:

	AActor* GetGridNodeBelowTowerPreview();
	bool CheckIfPlacedOnNode();
	bool CheckIfNodeOccupied();
	bool CheckIfTowerBlocksPath();
	bool CheckCanReplaceOccupyingTower();
	void ExecutePlaceTowerSequence();
	void PlaceTower();

	AA_UI_Manager* UI_Manager;

	AA_Tower* PreviewTower;
	TSubclassOf<class AA_Tower> PreviewTowerClass;
	AA_Tower* TowerOccupyingGridNodeBelow;

	FVector EnemySpawnLocation;
	FVector EndGoalLocation;

	int Points;
	int NewWavePointsAwarded;
	bool PlayerHoldingTower;
};
