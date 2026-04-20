#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "Item_ShootingPannel.generated.h"

UCLASS()
class NBC_DOWORK_08_API AItem_ShootingPannel : public ABaseItem
{
	GENERATED_BODY()

public:
	AItem_ShootingPannel();
protected:
	virtual void BeginPlay() override;
public:
	virtual void HitItem() override;
};
