
#pragma once

#include "CoreMinimal.h"

#include "A_Tower.h"
#include "I_GridNode.h"

#include "A_GridNode.generated.h"

UCLASS()
class INCURSION_CPP_API AA_GridNode : public AActor, public II_GridNode
{
	GENERATED_BODY()
	
public:	
	AA_GridNode();

	virtual void SetOccupied(bool IsOccupied, AA_Tower* OccupyingTowerRef) override;
	virtual bool GetOccupied() override;
	virtual AA_Tower* GetOccupyingTower() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* PlaneMesh;

private:
	bool Occupied;
	AA_Tower* OccupyingTower;
};
