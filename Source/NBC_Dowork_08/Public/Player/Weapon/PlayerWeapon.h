#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerWeapon.generated.h"

UCLASS()
class NBC_DOWORK_08_API APlayerWeapon : public AActor
{
	GENERATED_BODY()

public:
	APlayerWeapon();
	FORCEINLINE UStaticMeshComponent* GetWeaponMesh() const{return MeshComp;}

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Mesh")
	TObjectPtr<USceneComponent> SceneComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Mesh")
	TObjectPtr<UStaticMeshComponent> MeshComp;
};
