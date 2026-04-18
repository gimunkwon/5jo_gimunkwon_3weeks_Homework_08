#include "Player/Controller/ShootingPlayerControlloer.h"
#include "EnhancedInputSubsystems.h"
#include "Compute/ComputeSocket.h"

AShootingPlayerControlloer::AShootingPlayerControlloer()
{
	
}

void AShootingPlayerControlloer::BeginPlay()
{
	Super::BeginPlay();
	
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(GetLocalPlayer()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubSystem = Cast<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()))
		{
			UE_LOG(LogTemp,Warning,TEXT("IMC_MappingSuccess!"))
			EnhancedInputSubSystem->AddMappingContext(IMC_PlayerDefault,0);
		}
	}
}
