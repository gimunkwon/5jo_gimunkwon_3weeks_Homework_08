#include "NBC_Dowork_08/Public/Player/ShootingPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "Player/Animations/ShootingPlayerAnimInst.h"
#include "Player/Controller/ShootingPlayerControlloer.h"
#include "Player/Weapon/PlayerWeapon.h"


AShootingPlayer::AShootingPlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 0.f;
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;
}


void AShootingPlayer::BeginPlay()
{
	Super::BeginPlay();
	EquipWeapon();
}


void AShootingPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	
	if (!FMath::IsNearlyZero(RotateValue.X))
	{
		AddControllerPitchInput(RotateValue.X);
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
}

void AShootingPlayer::StartZoom()
{
	UE_LOG(LogTemp,Warning,TEXT("StartZoom"));
	if (AM_Zoom)
	{
		if (UShootingPlayerAnimInst* MyAnimInst = Cast<UShootingPlayerAnimInst>(GetMesh()->GetAnimInstance()))
		{
			MyAnimInst->Montage_Play(AM_Zoom);
			MyAnimInst->bSetbIszooming(true);
		}
	}
}

void AShootingPlayer::EndZoom()
{
	UE_LOG(LogTemp,Warning,TEXT("EndZoom"));
	if (UShootingPlayerAnimInst* MyAnimInst = Cast<UShootingPlayerAnimInst>(GetMesh()->GetAnimInstance()))
	{
		MyAnimInst->bSetbIszooming(false);
	}
}

void AShootingPlayer::EquipWeapon()
{
	if (WeaponClass)
	{
		AActor* NewWeapon = GetWorld()->SpawnActor<APlayerWeapon>(WeaponClass,FVector::ZeroVector,FRotator::ZeroRotator);
		
		if (NewWeapon)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
			
			NewWeapon->AttachToComponent(GetMesh(), AttachmentRules, TEXT("Weapon"));
		}
		
	}
	
}
