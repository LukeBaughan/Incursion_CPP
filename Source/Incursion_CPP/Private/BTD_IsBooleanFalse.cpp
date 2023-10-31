
#include "BTD_IsBooleanFalse.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTD_IsBooleanFalse::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("%s"), !(OwnerComp.GetBlackboardComponent()->GetValueAsBool((BooleanVariableKey.SelectedKeyName))) ? TEXT("true") : TEXT("false")));

	return !(OwnerComp.GetBlackboardComponent()->GetValueAsBool((BooleanVariableKey.SelectedKeyName)));
}