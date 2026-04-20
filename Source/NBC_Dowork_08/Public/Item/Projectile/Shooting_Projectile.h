#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shooting_Projectile.generated.h"

UCLASS()
class NBC_DOWORK_08_API AShooting_Projectile : public AActor
{
	GENERATED_BODY()
public:
	AShooting_Projectile();
protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;
};
