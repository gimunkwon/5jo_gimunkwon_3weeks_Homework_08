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
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Time")
	float RotateTime;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Projectile")
	TSubclassOf<AActor> ProjectileClass;
	
	FTimerHandle RotateTimerHandle;
	
	void RotateItem(float DeltaTime);
	void FireToPlayer();
	
private:
	float RotateAngle;
	bool bEndRotate;
	float CurrentRotateValue;
public:
	virtual void HitItem() override;
	virtual void Tick(float DeltaSeconds) override;
};

