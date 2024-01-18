
#include "SG_Incursion.h"

USG_Incursion::USG_Incursion() :
	EnemiesKilled(0),
	TotalPoints(0),
	PlayerDeaths(0),
	GamesPlayed(0),
	GamesWon(0),
	SoundClassVolumesSize(3)
{
	for (int SoundClassVolumesIndex = 0; SoundClassVolumesIndex < SoundClassVolumesSize; SoundClassVolumesIndex++)
	{
		SoundClassVolumes.Add(1.0f);
	}
}