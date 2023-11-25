
#include "A_StatsManager.h"

#include "Kismet/GameplayStatics.h"

AA_StatsManager::AA_StatsManager() :
	SaveGameInstance(nullptr),
	SaveFileName("Incursion Save File")
{
}

void AA_StatsManager::Initialise()
{
	// Loads the save game file
	USaveGame* LoadedSaveGame = UGameplayStatics::LoadGameFromSlot(SaveFileName, 0);

	if (IsValid(LoadedSaveGame))
	{
		SaveGameInstance = Cast<USG_Incursion>(LoadedSaveGame);
	}
	// If there is no save game, create it
	else
	{
		SaveGameInstance = Cast<USG_Incursion>(UGameplayStatics::CreateSaveGameObject(USG_Incursion::StaticClass()));
	}
}

void AA_StatsManager::IncrementEnemiesKilled()
{
	SaveGameInstance->EnemiesKilled++;	
	UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveFileName, 0);
}

void AA_StatsManager::IncrementPlayerDeaths()
{
	SaveGameInstance->PlayerDeaths++;
	UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveFileName, 0);
}

void AA_StatsManager::IncreaseTotalPoints(int Amount)
{
	SaveGameInstance->TotalPoints+= Amount;
	UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveFileName, 0);
}

void AA_StatsManager::IncrementGamesPlayed()
{
	SaveGameInstance->GamesPlayed++;
	UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveFileName, 0);
}

void AA_StatsManager::IncrementGamesWon()
{
	SaveGameInstance->GamesPlayed++;
	SaveGameInstance->GamesWon++;
	UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveFileName, 0);
}
