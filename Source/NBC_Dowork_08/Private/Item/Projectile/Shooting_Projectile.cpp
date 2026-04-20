#include "Item/Projectile/Shooting_Projectile.h"

#include "Components/BoxComponent.h"
#include "Player/ShootingPlayer.h"


AShooting_Projectile::AShooting_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComp;
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponentCollision"));
	BoxComp->SetupAttachment(SceneComp);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(SceneComp);
	StaticMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AShooting_Projectile::OnOverlapBegin);
}


void AShooting_Projectile::BeginPlay()
{
	Super::BeginPlay();
}

void AShooting_Projectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag(TEXT("Player")))
	{
		UE_LOG(LogTemp,Warning,TEXT("Bullet OverlapBegin!!"));
	}
	
}


