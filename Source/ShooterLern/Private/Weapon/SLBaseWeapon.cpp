// Project Shooter with c++


#include "Weapon/SLBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

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
	
}

void ASLBaseWeapon::Fire()
{
	UE_LOG(LogBaseWeapon, Display, TEXT("Fire"));
}


