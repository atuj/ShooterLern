// Project Shooter with c++


#include "Weapon/SLRifleWeaponBase.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/SLWeaponFXComponent.h"
#include "..\..\..\..\..\UE5\UE_5.0\Engine\Plugins\FX\Niagara\Source\Niagara\Public\NiagaraComponent.h"
#include "..\..\..\..\..\UE5\UE_5.0\Engine\Plugins\FX\Niagara\Source\Niagara\Public\NiagaraFunctionLibrary.h"

void ASLRifleWeaponBase::StartFire()
{
	InitMuzzleFX();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASLRifleWeaponBase::MakeShot, TimerBetweenShots, true);
	MakeShot();
}

ASLRifleWeaponBase::ASLRifleWeaponBase()
{
	WeaponFXComponent = CreateDefaultSubobject<USLWeaponFXComponent>("WeaponFXComponent");
}

void ASLRifleWeaponBase::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetMuzzleFXVisibility(false);
}

void ASLRifleWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);
}

void ASLRifleWeaponBase::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);


	FVector TraceFXEnd = TraceEnd;
	if (HitResult.bBlockingHit)
	{
		TraceFXEnd = HitResult.ImpactPoint;
		MakeDamage(HitResult);
		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	SpawnTraceFX(GetMuzzleWorldLocation(),TraceFXEnd);
	DecreaseAmmo();
}

bool ASLRifleWeaponBase::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation; //SocketTransform.GetLocation();
	const auto HalfRad = FMath::DegreesToRadians(BulletSprad);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	//SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void ASLRifleWeaponBase::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;
	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}

void ASLRifleWeaponBase::InitMuzzleFX()
{
	if(!MuzzleFXComponent)
	{
		MuzzleFXComponent=SpawnMuzzleFX();
	}
	SetMuzzleFXVisibility(true);
}

void ASLRifleWeaponBase::SetMuzzleFXVisibility(bool Visibility)
{
	if(MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!Visibility);
		MuzzleFXComponent->SetVisibility(Visibility,true);
	}
}

void ASLRifleWeaponBase::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),TraceFX,TraceStart);
	if(TraceFXComponent)
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName,TraceEnd);
	}
}


