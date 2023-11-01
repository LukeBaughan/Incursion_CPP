
#include "BTS_GetEnemyData.h"

void UBTS_GetEnemyData::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	EnemyInterface = Cast<II_Enemy>(OwnerComp.GetAIOwner()->GetPawn());

	if (EnemyInterface)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AttackReadyKey.SelectedKeyName, EnemyInterface->GetAttackReady());
	}
}