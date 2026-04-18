#include "Player/Animations/ShootingPlayerAnimInst.h"

#include "Player/ShootingPlayer.h"

void UShootingPlayerAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if (!MyOwnerPlayer)
	{
		MyOwnerPlayer = Cast<AShootingPlayer>(TryGetPawnOwner());
	}
	bIsZooming = false;
}

void UShootingPlayerAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (MyOwnerPlayer)
	{
		FVector Velocity = MyOwnerPlayer->GetVelocity();
		Speed = Velocity.Size2D();
	}
}

void UShootingPlayerAnimInst::bSetbIszooming(bool biszooming)
{
	bIsZooming = biszooming;
}
