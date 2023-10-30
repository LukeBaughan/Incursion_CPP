
#include "A_WaveManager.h"

#include "C_Enemy.h"
#include "A_EnemySpawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AA_WaveManager::AA_WaveManager()
{
	EnemySpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// make into function? (when there are many classes)
	ConstructorHelpers::FClassFinder<class AC_Enemy> EnemyStandard_CF(TEXT("/Game/Luke/Enemy/C_Enemy_Standard_BP"));
	if (EnemyStandard_CF.Succeeded())
	{
		EnemyClasses[E_EnemyClass::Standard] = EnemyStandard_CF.Class;
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("A_WaveManager: Unable to set EnemyClasses[E_EnemyClass::Standard]"));
	}
}

void AA_WaveManager::Initialise()
{
	GetEnemySpawnLocation();
}

void AA_WaveManager::GetEnemySpawnLocation()
{
	EnemySpawnLocation = UGameplayStatics::GetActorOfClass(GetWorld(), AA_EnemySpawn::StaticClass())->GetRootComponent()->GetComponentLocation();
}

void AA_WaveManager::BeginWaveCountdown()
{
	SpawnEnemy(EnemyClasses[E_EnemyClass::Standard]);
}

void AA_WaveManager::SpawnEnemy(TSubclassOf<class AC_Enemy> EnemyClass)
{
	AC_Enemy* Enemy = GetWorld()->SpawnActor<AC_Enemy>(EnemyClass, EnemySpawnLocation, FRotator::ZeroRotator, EnemySpawnParameters);
	Enemy->SpawnDefaultController();
}
