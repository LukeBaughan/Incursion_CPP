
#include "A_WaveManager.h"

#include "C_Enemy.h"
#include "A_EnemySpawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AA_WaveManager::AA_WaveManager() :
	WidgetHUD_Timer(nullptr),
//	WidgetSkipCountdown(nullptr),
	EnemySpawnLocation(FVector::ZeroVector),
	CurrentWave(6),
	EnemySpawnIndex(0),
	TotalNumberOfEnemiesThisWave(0),
	EnemiesDefeatedOrReachedGoalThisWave(0),
	EnemySpawnRate(1.0f)
{
	EnemySpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// DEPRECIATED
	GetEnemyClassReference(E_EnemyClass::Standard, TEXT("C_Enemy_Standard_BP"));
	GetEnemyClassReference(E_EnemyClass::Runner, TEXT("C_Enemy_Runner_BP"));
	GetEnemyClassReference(E_EnemyClass::Maverick, TEXT("C_Enemy_Maverick_BP"));
	GetEnemyClassReference(E_EnemyClass::Heavy, TEXT("C_Enemy_Heavy_BP"));
	GetEnemyClassReference(E_EnemyClass::Behemoth, TEXT("C_Enemy_Behemoth_BP"));
}

// DEPRECIATED
void AA_WaveManager::GetEnemyClassReference(E_EnemyClass EnemyClass, FString EnemyBP_FileName)
{
	FString EnemyFilePath = TEXT("/Game/Luke/Enemy/") + EnemyBP_FileName;

	ConstructorHelpers::FClassFinder<class AC_Enemy> EnemyCF(*EnemyFilePath);
	if (EnemyCF.Succeeded())
	{
		EnemyClasses[EnemyClass] = EnemyCF.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, (TEXT("A_WaveManager: Unable to get Enemy")));
	}
}


//void AA_WaveManager::Initialise(UW_HUD_Timer* WidgetHUD_TimerRef, UW_SkipCountdown* WidgetSkipCountdownRef)
//{
//	WidgetHUD_Timer = WidgetHUD_TimerRef;
//	//WidgetSkipCountdown = WidgetSkipCountdownRef;
//	GetWaveData();
//	GetEnemySpawnLocation();
//}

void AA_WaveManager::GetWaveData()
{
	AllWaveEnemies = Cast<AA_WaveData>(UGameplayStatics::GetActorOfClass(GetWorld(), AA_WaveData::StaticClass()))->AllWaveEnemies;

	if (AllWaveEnemies.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("A_WaveManager: Unable to get AllWaveEnemies"));
	}
}

void AA_WaveManager::GetEnemySpawnLocation()
{
	EnemySpawnLocation = UGameplayStatics::GetActorOfClass(GetWorld(), AA_EnemySpawn::StaticClass())->GetRootComponent()->GetComponentLocation();
}

void AA_WaveManager::BeginWaveCountdown()
{
	BeginWave();
}

void AA_WaveManager::BeginWave()
{
	++CurrentWave;
	EnemySpawnIndex = 0;
	EnemiesDefeatedOrReachedGoalThisWave = 0;
	CurrentWaveEnemies = AllWaveEnemies[CurrentWave - 1].Enemies;
	TotalNumberOfEnemiesThisWave = CurrentWaveEnemies.Num();

	GetWorldTimerManager().SetTimer(TH_SpawningEnemies, this, &AA_WaveManager::DecideSpawnEnemyClass, EnemySpawnRate, true);

}

// Iterates through the current wave data arrayand spawns the specified enemies
void AA_WaveManager::DecideSpawnEnemyClass()
{
	if(EnemySpawnIndex < CurrentWaveEnemies.Num())
	{
		SpawnEnemy(CurrentWaveEnemies[EnemySpawnIndex]);
		++EnemySpawnIndex;
	}
	else
	{
		//If the end of the array has been reached, end the spawn timer
		GetWorldTimerManager().ClearTimer(TH_SpawningEnemies);
	}
}

void AA_WaveManager::SpawnEnemy(TSubclassOf<class AC_Enemy> EnemyClass)
{
	AC_Enemy* Enemy = GetWorld()->SpawnActor<AC_Enemy>(EnemyClass, EnemySpawnLocation, FRotator::ZeroRotator, EnemySpawnParameters);
	Enemy->SpawnDefaultController();
	Enemy->Initialise();
	Enemy->OnGoalReached.AddDynamic(this, &AA_WaveManager::OnEnemyGoalReached);
	Enemy->OnDefeated.AddDynamic(this, &AA_WaveManager::OnEnemyDefeated);
}

void AA_WaveManager::OnEnemyGoalReached(uint8 LivesCost)
{
	OnRequestLoseLives.Broadcast(LivesCost);
}

void AA_WaveManager::OnEnemyDefeated(AC_Enemy* Enemy, int PointsRewarded)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("A_WaveManager: %d Points Rewarded"), PointsRewarded));
}
