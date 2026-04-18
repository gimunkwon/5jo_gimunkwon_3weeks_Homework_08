#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShootingPlayerAnimInst.generated.h"

class AShootingPlayer;

UCLASS()
class NBC_DOWORK_08_API UShootingPlayerAnimInst : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	FORCEINLINE void bSetbIszooming(bool biszooming);
	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PlayerInstance")
	TObjectPtr<AShootingPlayer> MyOwnerPlayer;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Speed")
	float Speed;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="CameraEffet")
	bool bIsZooming;
};
