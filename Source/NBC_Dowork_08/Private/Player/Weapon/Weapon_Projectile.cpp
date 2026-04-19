#include "Player/Weapon/Weapon_Projectile.h"



AWeapon_Projectile::AWeapon_Projectile()
{
	
	PrimaryActorTick.bCanEverTick = true;
}


void AWeapon_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}


void AWeapon_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

