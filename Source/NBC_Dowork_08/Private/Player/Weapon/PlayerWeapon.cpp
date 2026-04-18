#include "Player/Weapon/PlayerWeapon.h"


APlayerWeapon::APlayerWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComp;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	MeshComp->SetupAttachment(SceneComp);
	
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));
}


void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}



