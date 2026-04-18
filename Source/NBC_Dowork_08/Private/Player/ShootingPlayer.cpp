#include "NBC_Dowork_08/Public/Player/ShootingPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


AShootingPlayer::AShootingPlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 0.f;
	SpringArmComp->bUsePawnControlRotation = false;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;
}


void AShootingPlayer::BeginPlay()
{
	Super::BeginPlay();
}


void AShootingPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AShootingPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

