
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
	UFUNCTION(BlueprintNativeEvent)
		void ShowWalls(FVector PlacedTowerPosition);

	virtual void ShowWalls_Implementation(FVector PlacedTowerPosition);
};
