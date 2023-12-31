
#include "A_WaveManager.h"

#include "C_Enemy.h"
#include "A_EnemySpawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AA_WaveManager::AA_WaveManager() :
	WidgetHUD_Timer(nullptr),
	WidgetHUD_SkipCountdown(nullptr),
	MaxCountdownTime(30),
	CurrentCountdownTime(0),
	EnemySpawnLocation(FVector::ZeroVector),
	EnemySpawnRotation(FRotator::ZeroRotator),
	CurrentWave(0),
	EnemySpawnIndex(0),
	TotalNumberOfEnemiesThisWave(0),
	EnemiesDefeatedOrReachedGoalThisWave(0),
	EnemySpawnRate(1.0f),
	MaxWaves(10)
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


void AA_WaveManager::Initialise(UW_HUD_Timer* WidgetHUD_TimerRef, UW_HUD_SkipCountdown* WidgetSkipCountdownRef)
{
	WidgetHUD_Timer = WidgetHUD_TimerRef;
	WidgetHUD_SkipCountdown = WidgetSkipCountdownRef;
	GetWaveData();
	GetEnemySpawnTransform();
}

void AA_WaveManager::GetWaveData()
{
	AllWaveEnemies = Cast<AA_WaveData>(UGameplayStatics::GetActorOfClass(GetWorld(), AA_WaveData::StaticClass()))->AllWaveEnemies;

	if (AllWaveEnemies.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("A_WaveManager: Unable to get AllWaveEnemies"));
	}
}

void AA_WaveManager::GetEnemySpawnTransform()
{
	AActor* EnemySpawn = UGameplayStatics::GetActorOfClass(GetWorld(), AA_EnemySpawn::StaticClass());
	
	EnemySpawnLocation = EnemySpawn->GetActorLocation();
	EnemySpawnRotation = EnemySpawn->GetActorRotation();
}

void AA_WaveManager::BeginWaveCountdown()
{
	OnWaveEnded.Broadcast();

	// Requests to end the game if the final wave has been reached
	if (CurrentWave == MaxWaves)
	{
		OnGameWon.Broadcast();
	}

	WidgetHUD_Timer->SetVisibility(ESlateVisibility::Visible);
	WidgetHUD_SkipCountdown->SetVisibility(ESlateVisibility::Visible);

	// Resets the countdown number 
	CurrentCountdownTime = MaxCountdownTime;
	WidgetHUD_Timer->SetCountdownTime(CurrentCountdownTime);

	GetWorldTimerManager().SetTimer(TH_Countdown, this, &AA_WaveManager::Countdown, 1.0f, true);
}

// Updates the countdown timer
void AA_WaveManager::Countdown()
{
	--CurrentCountdownTime;
	CurrentCountdownTime = FMath::Clamp(CurrentCountdownTime, 0, MaxCountdownTime);
	WidgetHUD_Timer->SetCountdownTime(CurrentCountdownTime);

	// When the timer reaches 0, end it, hide the countdown UI, destroy all dead enemies and begin the next wave
	if (CurrentCountdownTime == 0)
	{
		GetWorldTimerManager().ClearTimer(TH_Countdown);
		WidgetHUD_Timer->SetVisibility(ESlateVisibility::Collapsed);

		for (AC_Enemy* Enemy : DeadEnemies)
		{
			if (IsValid(Enemy))
			{
				if(!Enemy->IsPendingKillPending())
				{
					Enemy->DestroySelf();
				}
			}
		}

		DeadEnemies.Empty();

		BeginWave();
	}
}

void AA_WaveManager::SkipCountdown()
{
	if (CurrentCountdownTime > 4)
	{
		CurrentCountdownTime = 4;
		WidgetHUD_SkipCountdown->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AA_WaveManager::BeginWave()
{
	++CurrentWave;
	OnWaveBegin.Broadcast(CurrentWave, AllWaveEnemies.Num());
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
	AC_Enemy* Enemy = GetWorld()->SpawnActor<AC_Enemy>(EnemyClass, EnemySpawnLocation, EnemySpawnRotation, EnemySpawnParameters);
	Enemy->SpawnDefaultController();
	Enemy->Initialise();
	Enemy->OnGoalReached.AddDynamic(this, &AA_WaveManager::OnEnemyGoalReached);
	Enemy->OnDefeated.AddDynamic(this, &AA_WaveManager::OnEnemyDefeated);
}

// If the number of enemies defeated or have reached the goal is equal to the number of enemies this wave, count down the next wave
void AA_WaveManager::IncrementEnemiesDefeatedOrReachedGoal()
{
	++EnemiesDefeatedOrReachedGoalThisWave;

	if (EnemiesDefeatedOrReachedGoalThisWave == TotalNumberOfEnemiesThisWave)
	{
		BeginWaveCountdown();
	}
}

void AA_WaveManager::OnEnemyGoalReached(uint8 LivesCost)
{
	OnRequestLoseLives.Broadcast(LivesCost);
	IncrementEnemiesDefeatedOrReachedGoal();
}

void AA_WaveManager::OnEnemyDefeated(AC_Enemy* Enemy, int PointsRewarded)
{
	DeadEnemies.Add(Enemy);
	IncrementEnemiesDefeatedOrReachedGoal();
	OnRequestPoints.Broadcast(PointsRewarded);
	OnEnemyDefeatedDelegate.Broadcast();
}
