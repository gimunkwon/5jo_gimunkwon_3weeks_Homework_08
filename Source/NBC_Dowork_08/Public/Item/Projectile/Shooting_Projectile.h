#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shooting_Projectile.generated.h"

class UBoxComponent;

UCLASS()
class NBC_DOWORK_08_API AShooting_Projectile : public AActor
{
	GENERATED_BODY()
public:
	AShooting_Projectile();
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp
		, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);

	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Mesh")
	TObjectPtr<USceneComponent> SceneComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Mesh")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Collision")
	TObjectPtr<UBoxComponent> BoxComp;
};
