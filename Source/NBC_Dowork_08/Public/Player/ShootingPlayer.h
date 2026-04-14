#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootingPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class NBC_DOWORK_08_API AShootingPlayer : public ACharacter
{
	GENERATED_BODY()
public:
	AShootingPlayer();
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArmComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera")
	TObjectPtr<UCameraComponent> CameraComp;
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
