#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BaseHitItem.generated.h"


UINTERFACE()
class UBaseHitItem : public UInterface
{
	GENERATED_BODY()
};

class NBC_DOWORK_08_API IBaseHitItem
{
	GENERATED_BODY()
public:
	virtual void HitItem() = 0;
};
