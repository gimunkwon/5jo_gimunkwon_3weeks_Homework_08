#include "Item/Projectile/Shooting_Projectile.h"



AShooting_Projectile::AShooting_Projectile()
{
	
	PrimaryActorTick.bCanEverTick = true;
}


void AShooting_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}


void AShooting_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

