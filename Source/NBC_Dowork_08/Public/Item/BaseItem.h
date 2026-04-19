#pragma once

#include "CoreMinimal.h"
#include "BaseHitItem.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UCLASS()
class NBC_DOWORK_08_API ABaseItem : public AActor , public IBaseHitItem
{
	GENERATED_BODY()

public:
	ABaseItem();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void HitItem() override;
};
