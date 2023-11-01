
#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BTService.h"
#include "I_Enemy.h"

#include "BTS_GetEnemyData.generated.h"

/**
 * 
 */
UCLASS()
class INCURSION_CPP_API UBTS_GetEnemyData : public UBTService
{
	GENERATED_BODY()

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "BP Keys")
		FBlackboardKeySelector AttackReadyKey;	

private:
	II_Enemy* EnemyInterface;
};
