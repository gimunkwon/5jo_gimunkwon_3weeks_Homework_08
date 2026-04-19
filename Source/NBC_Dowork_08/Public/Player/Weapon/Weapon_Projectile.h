#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Projectile.generated.h"

UCLASS()
class NBC_DOWORK_08_API AWeapon_Projectile : public AActor
{
	GENERATED_BODY()

public:
	
	AWeapon_Projectile();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
};
