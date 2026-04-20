#include "Item/Ballon/Item_Ballon.h"



AItem_Ballon::AItem_Ballon()
{
	PrimaryActorTick.bCanEverTick = false;
	Item_Score = 20;
}


void AItem_Ballon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem_Ballon::HitItem()
{
	Super::HitItem();
}


