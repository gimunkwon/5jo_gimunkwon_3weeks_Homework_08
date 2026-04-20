#include "Item/ShootingPannel/Item_ShootingPannel.h"



AItem_ShootingPannel::AItem_ShootingPannel()
{
	
	PrimaryActorTick.bCanEverTick = false;
}


void AItem_ShootingPannel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem_ShootingPannel::HitItem()
{
	Super::HitItem();
}

