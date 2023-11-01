
#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BTTaskNode.h"
#include "I_Character.h"
#include "I_Enemy.h"

#include "BTT_AttackPlayer.generated.h"

UCLASS()
class INCURSION_CPP_API UBTT_AttackPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	APawn* ControlledEnemy;
	II_Enemy* EnemyInterface;
	USkeletalMeshComponent* EnemyBodyMesh;
	UAnimInstance* EnemyAttackAnimInstance;

	II_Character* PlayerCharacterInterface;
};
