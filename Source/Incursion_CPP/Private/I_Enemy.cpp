
#include "I_Enemy.h"

// Add default functionality here for any II_Enemy functions that are not pure virtual.


bool II_Enemy::GetPlayerInFollowRange()
{
	return false;
}

bool II_Enemy::GetPlayerInAttackRange()
{
	return false;
}

bool II_Enemy::GetAttackReady()
{
	return false;
}

float II_Enemy::GetAttackDamage()
{
	return 0.0f;
}

void II_Enemy::OnAttackExecuted()
{
}

USkeletalMeshComponent* II_Enemy::GetBodyMesh()
{
	return nullptr;
}

USoundBase* II_Enemy::GetAttackSound()
{
	return nullptr;
}

UAnimMontage* II_Enemy::GetAttackAnimation()
{
	return nullptr;
}
