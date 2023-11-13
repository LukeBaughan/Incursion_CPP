
#pragma once

#include "CoreMinimal.h"

#include "A_Tower.h"
#include "UObject/Interface.h"

#include "I_GridNode.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_GridNode : public UInterface
{
	GENERATED_BODY()
};

class INCURSION_CPP_API II_GridNode
{
	GENERATED_BODY()

public:
	virtual void SetOccupied(bool IsOccupied, AA_Tower* OccupyingTowerRef);
	virtual bool GetOccupied();
	virtual AA_Tower* GetOccupyingTower();
};
