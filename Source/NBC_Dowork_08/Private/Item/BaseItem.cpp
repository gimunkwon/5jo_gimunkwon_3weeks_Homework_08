#include "Item/BaseItem.h"



ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComp;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(SceneComp);
	
	Item_Score = 0;
}


void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseItem::HitItem()
{
	UE_LOG(LogTemp,Warning,TEXT("Hit Item Success!!"))
	Destroy();
}

