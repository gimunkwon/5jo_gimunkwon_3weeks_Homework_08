#include "Item/ShootingPannel/Item_ShootingPannel.h"

#include "Item/Projectile/Shooting_Projectile.h"


AItem_ShootingPannel::AItem_ShootingPannel()
{
	PrimaryActorTick.bCanEverTick = true;
	Item_Score = 20;
	RotateTime = 2.f;
	RotateAngle = 180.f;
	bEndRotate = false;
	CurrentRotateValue = 0.f;
}


void AItem_ShootingPannel::BeginPlay()
{
	Super::BeginPlay();
}

void AItem_ShootingPannel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	RotateItem(DeltaSeconds);
}

void AItem_ShootingPannel::RotateItem(float DeltaTime)
{
	
	if (CurrentRotateValue < 180.f && !bEndRotate)
	{
		float AddRotationValue = RotateAngle * DeltaTime;
		FRotator NewYawRotation(0.f, AddRotationValue, 0.f);
		CurrentRotateValue += AddRotationValue;
		
		AddActorLocalRotation(NewYawRotation);
	}
	else if (CurrentRotateValue >= 180.f)
	{
		SetActorRotation(FRotator(0.f, GetActorRotation().Yaw - CurrentRotateValue - 180.f, 0.f));
		bEndRotate = true;
		CurrentRotateValue = 0.f;
		
		FireToPlayer();
		
		GetWorldTimerManager().SetTimer(RotateTimerHandle,[this]()
		{
			bEndRotate = false;
		},2.f,false);
	}
	
}

void AItem_ShootingPannel::FireToPlayer()
{
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	
	FVector MuzzleLocation = StaticMeshComp->GetSocketLocation(TEXT("MuzzleSocket"));
	
	FVector ForwardVector = StaticMeshComp->GetSocketRotation(TEXT("MuzzleSocket")).Vector();
	
	float TraceDistance = 1000.f;
	FVector EndLocation = MuzzleLocation + ForwardVector * TraceDistance;
	
	
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult
		, MuzzleLocation, EndLocation, ECC_Visibility, CollisionParams);
	
	DrawDebugLine(GetWorld(), MuzzleLocation, EndLocation
		, FColor::Yellow, false, 2.f, 0, 2.f);
	
	if (ProjectileClass)
	{
		// 오브젝트 풀링 리팩토링 예정
		AActor* SpawnProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass,MuzzleLocation,GetActorRotation());
		
		if (SpawnProjectile)
		{
			FTimerHandle SpawnTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, [SpawnProjectile,this]()
			{
				float Velocity = GetWorld()->GetDeltaSeconds() * 200.f;
				FVector AddLocation(Velocity,0.f,0.f);
				SpawnProjectile->AddActorLocalOffset(AddLocation);
				FTimerHandle DestroyTimerHandle;
				GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, [SpawnProjectile,this]()
				{
					if (SpawnProjectile) SpawnProjectile->Destroy();
					
				},3.f,false);
			},0.01f, true);
		}
	}
	
}

void AItem_ShootingPannel::HitItem()
{
	Super::HitItem();
}



