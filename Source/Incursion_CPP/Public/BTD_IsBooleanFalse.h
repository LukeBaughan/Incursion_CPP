
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_IsBooleanFalse.generated.h"

UCLASS()
class INCURSION_CPP_API UBTD_IsBooleanFalse : public UBTDecorator
{
	GENERATED_BODY()

public:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = "BP Keys")
		FBlackboardKeySelector BooleanVariableKey;
	
};
