
#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BTService.h"
#include "I_Character.h"
#include "I_Enemy.h"

#include "BTS_GetPlayerData.generated.h"

UCLASS()
class INCURSION_CPP_API UBTS_GetPlayerData : public UBTService
{
	GENERATED_BODY()

public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "BP Keys")
		FBlackboardKeySelector PlayerLocationKey;

	UPROPERTY(EditAnywhere, Category = "BP Keys")
		FBlackboardKeySelector PlayerInFollowRangeKey;	
	
	UPROPERTY(EditAnywhere, Category = "BP Keys")
		FBlackboardKeySelector PlayerInAttackRange;

private:

	APawn* Player;
	II_Character* PlayerCharacterInterface;	
	II_Enemy* EnemyInterface;	
};
