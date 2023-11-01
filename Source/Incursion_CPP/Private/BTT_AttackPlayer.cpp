
#include "BTT_AttackPlayer.h"

#include "Kismet/Gameplaystatics.h"

EBTNodeResult::Type UBTT_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ControlledEnemy = OwnerComp.GetAIOwner()->GetPawn();

	EnemyInterface = Cast<II_Enemy>(ControlledEnemy);

	if (EnemyInterface)
	{
		if(EnemyInterface->GetAttackReady())
		{	
			EnemyInterface->OnAttackExecuted();

			EnemyBodyMesh = EnemyInterface->GetBodyMesh();
			UGameplayStatics::SpawnSoundAttached(EnemyInterface->GetAttackSound(), EnemyBodyMesh);
			EnemyAttackAnimInstance = EnemyBodyMesh->GetAnimInstance();
			EnemyAttackAnimInstance->Montage_Play(EnemyInterface->GetAttackAnimation(), 1.75);

			PlayerCharacterInterface = Cast<II_Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
			
			if (PlayerCharacterInterface)
			{
				PlayerCharacterInterface->TakeDamageCharacter(EnemyInterface->GetAttackDamage());
			}
		}
	}

	return EBTNodeResult::Type();
}