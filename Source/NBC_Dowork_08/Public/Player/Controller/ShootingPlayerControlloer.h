#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShootingPlayerControlloer.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class NBC_DOWORK_08_API AShootingPlayerControlloer : public APlayerController
{
	GENERATED_BODY()
	
public:
	AShootingPlayerControlloer();
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputMappingContext> IMC_PlayerDefault;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	TObjectPtr<UInputAction> IA_Look;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	TObjectPtr<UInputAction> IA_Move;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	TObjectPtr<UInputAction> IA_Jump;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	TObjectPtr<UInputAction> IA_Shoot;
};
