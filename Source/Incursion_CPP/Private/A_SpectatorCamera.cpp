
#include "A_SpectatorCamera.h"

AA_SpectatorCamera::AA_SpectatorCamera() :
	CameraComponent(CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent")))
{
	CameraComponent->SetupAttachment(RootComponent);
}