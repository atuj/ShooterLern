// Project Shooter with c++


#include "Weapon/SLBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

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
	checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count couldn`t be less or equal zero"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Clips count couldn`t be less or equal zero"));
	CurrentAmmo = DefaultAmmo;
}

void ASLBaseWeapon::StartFire()
{
}

void ASLBaseWeapon::StopFire()
{
}

void ASLBaseWeapon::MakeShot()
{
}

APlayerController* ASLBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

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
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation; //SocketTransform.GetLocation();
	//const auto HalfRad = FMath::DegreesToRadians(BulletSprad);
	const FVector ShootDirection = ViewRotation.Vector();
	//FMath::VRandCone( ViewRotation.Vector(), HalfRad);	//SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void ASLBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
	                                     CollisionParams);
}

void ASLBaseWeapon::DecreaseAmmo()
{
	if(CurrentAmmo.Bullets == 0)
	{
		UE_LOG(LogBaseWeapon,Warning,TEXT("Clips is empty"));
		return;
	}
	CurrentAmmo.Bullets--;
	if(IsClipsEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast(this);
	}
}
bool ASLBaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipsEmpty();
}
bool ASLBaseWeapon::IsClipsEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}
void ASLBaseWeapon::ChangeClip()
{
	if(!CurrentAmmo.Infinite)
	{
		if(CurrentAmmo.Clips == 0)
		{
			UE_LOG(LogBaseWeapon,Warning,TEXT("No more clips"));
			return;
		}
		CurrentAmmo.Clips--;
		UE_LOG(LogBaseWeapon,Display,TEXT("----- Change Clip -----"));
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
}

bool ASLBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

void ASLBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets)+ " / ";
	AmmoInfo+= CurrentAmmo.Infinite? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogBaseWeapon,Display,TEXT("%s"),*AmmoInfo);
}

bool ASLBaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool ASLBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
	if(CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;
	if(IsAmmoEmpty())
	{
		CurrentAmmo.Clips = FMath::Clamp( ClipsAmount,0,DefaultAmmo.Clips+1);
		OnClipEmpty.Broadcast(this);
	}
	else if(CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
		if(DefaultAmmo.Clips - NextClipsAmount >=0)
		{
			CurrentAmmo.Clips = NextClipsAmount;
		}
		else
		{
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		}
	}
	else
	{
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	}
	return true;
}


