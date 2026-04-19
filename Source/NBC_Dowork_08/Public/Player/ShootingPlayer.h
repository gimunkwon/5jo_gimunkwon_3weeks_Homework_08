#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootingPlayer.generated.h"

class APlayerWeapon;
struct FInputActionValue;
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
	
	// UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera")
	// TObjectPtr<USpringArmComponent> SpringArmComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera")
	TObjectPtr<UCameraComponent> CameraComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AnimMontage")
	TObjectPtr<UAnimMontage> AM_Zoom;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
	TSubclassOf<AActor> WeaponClass;
	UPROPERTY()
	TObjectPtr<APlayerWeapon> WeaponInstance;
	
	
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void StartJump(const FInputActionValue& value);
	void EndJump();
	void Shoot(const FInputActionValue& value);
	void StartZoom();
	void EndZoom();
	
	void EquipWeapon();
	void MoveToGunView(float deltatime);

private:
	FVector OriginCamLocation;
	FRotator OriginCamArmRotation;
	bool bIsZooming;
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
