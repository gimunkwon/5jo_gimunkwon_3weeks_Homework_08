#include "Player/Weapon/Weapon_Projectile.h"

AWeapon_Projectile::AWeapon_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComp;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(SceneComp);
	StaticMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
}


void AWeapon_Projectile::BeginPlay()
{
	Super::BeginPlay();
}


