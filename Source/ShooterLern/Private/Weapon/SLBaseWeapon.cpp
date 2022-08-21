// Project Shooter with c++


#include "Weapon/SLBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"


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


