
#include "A_WaveData.h"

// Sets default values
AA_WaveData::AA_WaveData() :
	BillboardComponent(CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComponent")))
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Creates the editor viewport icon and attaches it to the root component
	BillboardComponent->SetupAttachment(RootComponent);
}