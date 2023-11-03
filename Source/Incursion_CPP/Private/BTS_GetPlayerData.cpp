
#include "BTS_GetPlayerData.h"


#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "I_Character.h"
#include "Kismet/GameplayStatics.h"

void UBTS_GetPlayerData::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Expensive?
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	PlayerCharacterInterface = Cast<II_Character>(Player);

	if (PlayerCharacterInterface)
	{			
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(PlayerLocationKey.SelectedKeyName, Player->GetActorLocation());

		if (!PlayerCharacterInterface->GetIsDead())
		{
			EnemyInterface = Cast<II_Enemy>(OwnerComp.GetAIOwner()->GetPawn());

			if (EnemyInterface)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(PlayerInFollowRangeKey.SelectedKeyName, EnemyInterface->GetPlayerInFollowRange());
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(PlayerInAttackRange.SelectedKeyName, EnemyInterface->GetPlayerInAttackRange());
			}
		}
		else 
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(PlayerInFollowRangeKey.SelectedKeyName, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(PlayerInAttackRange.SelectedKeyName, false);
		}
	}
}