
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Tower.generated.h"

UINTERFACE(MinimalAPI)
class UI_Tower : public UInterface
{
	GENERATED_BODY()
};

class INCURSION_CPP_API II_Tower
{
	GENERATED_BODY()

public:
	virtual void ShowWalls(FVector PlacedTowerPosition);
};
