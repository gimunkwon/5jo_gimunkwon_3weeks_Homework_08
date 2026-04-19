#include "NBC_Dowork_08/Public/Player/ShootingPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/Animations/ShootingPlayerAnimInst.h"
#include "Player/Controller/ShootingPlayerControlloer.h"
#include "Player/Weapon/PlayerWeapon.h"


AShootingPlayer::AShootingPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	// SpringArmComp->SetupAttachment(RootComponent);
	// SpringArmComp->TargetArmLength = 0.f;
	// SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(RootComponent);
	CameraComp->bUsePawnControlRotation = true;
	
	bIsZooming = false;
}


void AShootingPlayer::BeginPlay()
{
	Super::BeginPlay();
	OriginCamLocation = CameraComp->GetRelativeLocation();
	OriginCamArmRotation = CameraComp->GetRelativeRotation();
	EquipWeapon();
}


void AShootingPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveToGunView(DeltaTime);
}


void AShootingPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AShootingPlayerControlloer* PC = Cast<AShootingPlayerControlloer>(GetController()))
		{
			EnhancedInputComp->BindAction(PC->IA_Move,ETriggerEvent::Triggered,this, &AShootingPlayer::Move);
			EnhancedInputComp->BindAction(PC->IA_Look,ETriggerEvent::Triggered,this, &AShootingPlayer::Look);
			EnhancedInputComp->BindAction(PC->IA_Shoot,ETriggerEvent::Started,this, &AShootingPlayer::Shoot);
			EnhancedInputComp->BindAction(PC->IA_Jump,ETriggerEvent::Started,this, &AShootingPlayer::StartJump);
			EnhancedInputComp->BindAction(PC->IA_Jump,ETriggerEvent::Completed,this, &AShootingPlayer::EndJump);
			EnhancedInputComp->BindAction(PC->IA_Zoom,ETriggerEvent::Started, this, &AShootingPlayer::StartZoom);
			EnhancedInputComp->BindAction(PC->IA_Zoom,ETriggerEvent::Completed,this,&AShootingPlayer::EndZoom);
		}
	}
	
}

void AShootingPlayer::Move(const FInputActionValue& value)
{
	FVector2D MoveValue = value.Get<FVector2D>();
	
	if (!FMath::IsNearlyZero(MoveValue.Y))
	{
		AddMovementInput(GetActorForwardVector(),MoveValue.Y);
	}
	
	if (!FMath::IsNearlyZero(MoveValue.X))
	{
		AddMovementInput(GetActorRightVector(),MoveValue.X);
	}
	
}

void AShootingPlayer::Look(const FInputActionValue& value)
{
	FVector2D RotateValue = value.Get<FVector2D>();
	
	FRotator NewRotatorX(RotateValue.X, 0.f, 0.f);
	FRotator NewRotatorY(0.f,0.f,RotateValue.Y);
	
	if (!FMath::IsNearlyZero(RotateValue.X))
	{
		float NewPitch = GetActorRotation().Pitch + NewRotatorX.Pitch;
		
		if (NewPitch >= -89.f && NewPitch <= 89.f)
		{
			AddActorLocalRotation(NewRotatorX);
		}
	}
	
	if (!FMath::IsNearlyZero(RotateValue.Y))
	{
		AddControllerYawInput(RotateValue.Y);
	}
}

void AShootingPlayer::StartJump(const FInputActionValue& value)
{
	Jump();
}

void AShootingPlayer::EndJump()
{
	StopJumping();
}

void AShootingPlayer::Shoot(const FInputActionValue& value)
{
	UE_LOG(LogTemp,Warning,TEXT("Shoot"));
	
	FVector CameraLocation;
	FRotator CameraRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(CameraLocation, CameraRotation);
	
	// CameraLocation.X += 100.f;
	// CameraLocation.Y += 100.f;
	CameraLocation.Z += 100.f;
	
	FVector TraceEnd = CameraLocation + (CameraRotation.Vector() * 10000.f);
	
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult,CameraLocation,TraceEnd, ECC_Visibility,Params);
	
	DrawDebugLine(GetWorld(),CameraLocation, bHit ? HitResult.ImpactPoint : TraceEnd, FColor::Red, false, 2.f, 0, 1.f);
	
	FVector TargetPoint = bHit ? HitResult.ImpactPoint : TraceEnd;
	
	FVector MuzzleLocation = WeaponInstance->GetWeaponMesh()->GetSocketLocation(TEXT("MuzzleSocket"));
	FRotator LaunchRotation = (TargetPoint - MuzzleLocation).Rotation();
	
	DrawDebugLine(GetWorld(),MuzzleLocation, bHit ? HitResult.ImpactPoint : TraceEnd, FColor::Green, false, 2.f, 0, 1.f);
	
	
}

void AShootingPlayer::StartZoom()
{
	// UE_LOG(LogTemp,Warning,TEXT("StartZoom"));
	if (AM_Zoom)
	{
		bIsZooming = true;
	}
}

void AShootingPlayer::EndZoom()
{
	// UE_LOG(LogTemp,Warning,TEXT("EndZoom"));
	bIsZooming = false;
}

void AShootingPlayer::EquipWeapon()
{
	if (WeaponClass)
	{
		AActor* NewWeapon = GetWorld()->SpawnActor<APlayerWeapon>(WeaponClass,FVector::ZeroVector,FRotator::ZeroRotator);
		
		WeaponInstance = Cast<APlayerWeapon>(NewWeapon);
		
		if (NewWeapon)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
			NewWeapon->AttachToComponent(GetMesh(), AttachmentRules, TEXT("WeaponSocket"));
		}
		
	}
}

void AShootingPlayer::MoveToGunView(float deltatime)
{
	if (bIsZooming && WeaponClass)
	{
		// UE_LOG(LogTemp,Warning,TEXT("MoveToGunViewON"));
		FTransform SightTransform = WeaponInstance->GetWeaponMesh()->GetSocketTransform(TEXT("SightSocket"));
		
		// DrawDebugCoordinateSystem(GetWorld(), SightTransform.GetLocation(), SightTransform.GetRotation().Rotator(),20.f);
		
		FVector TargetLocation = UKismetMathLibrary::InverseTransformLocation(GetRootComponent()->GetComponentTransform(), SightTransform.GetLocation());
		FRotator TargetRotation = UKismetMathLibrary::InverseTransformRotation(GetRootComponent()->GetComponentTransform(), SightTransform.GetRotation().Rotator());
		
		FVector NewLocation = FMath::VInterpTo(CameraComp->GetRelativeLocation(), TargetLocation, deltatime, 10.f);
		FRotator NewRotation = FMath::RInterpTo(CameraComp->GetRelativeRotation(), TargetRotation, deltatime, 10.f);
		
		CameraComp->SetRelativeLocation(NewLocation);
		CameraComp->SetRelativeRotation(NewRotation);
	}
	else
	{
		FVector NewLocation = FMath::VInterpTo(CameraComp->GetRelativeLocation(), OriginCamLocation, deltatime, 10.f);
		FRotator NewRotation = FMath::RInterpTo(CameraComp->GetRelativeRotation(), OriginCamArmRotation, deltatime, 10.f);
		
		CameraComp->SetRelativeLocation(NewLocation);
		CameraComp->SetRelativeRotation(NewRotation);
	}
}
