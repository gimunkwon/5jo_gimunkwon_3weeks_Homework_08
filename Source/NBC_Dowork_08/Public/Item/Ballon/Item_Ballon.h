#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "Item_Ballon.generated.h"

UCLASS()
class NBC_DOWORK_08_API AItem_Ballon : public ABaseItem
{
	GENERATED_BODY()

public:
	
	AItem_Ballon();

protected:
	
	virtual void BeginPlay() override;

public:
};
