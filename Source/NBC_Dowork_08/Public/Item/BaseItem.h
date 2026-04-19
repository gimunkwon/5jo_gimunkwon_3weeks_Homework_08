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
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Mesh")
	TObjectPtr<USceneComponent> SceneComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Mesh")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Score")
	int32 Item_Score;
	
public:
	virtual void HitItem() override;
};
