// Project Shooter with c++


#include "Weapon/SLBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon,All,All);

ASLBaseWeapon::ASLBaseWeapon()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

}


void ASLBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
	
}

void ASLBaseWeapon::StartFire()
{
	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASLBaseWeapon::MakeShot, TimerBetweenShots, true);
}
void ASLBaseWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASLBaseWeapon::MakeShot()
{
	if(!GetWorld()) return;

	FVector TraceStart, TraceEnd;
	if(!GetTraceData(TraceStart,TraceEnd)) return;
	
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	
	if(HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,10.0f,24,FColor::Red,false,5.0f);
		
	} else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	};
}

APlayerController* ASLBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if(!Player) return nullptr;
	
	return Player->GetController<APlayerController>();
}

bool ASLBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if (!Controller) return false;


	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

FVector ASLBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASLBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation,ViewRotation)) return false;

	TraceStart = ViewLocation;								//SocketTransform.GetLocation();
	const auto HalfRad = FMath::DegreesToRadians(BulletSprad);
	const FVector ShootDirection = FMath::VRandCone( ViewRotation.Vector(), HalfRad);	//SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void ASLBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd )
{
	
	if(!GetWorld()) return;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,CollisionParams);

}

void ASLBaseWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if(!DamagedActor) return;
	DamagedActor->TakeDamage(DamageAmount,FDamageEvent(),GetPlayerController(),this);

}

