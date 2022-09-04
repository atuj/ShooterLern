// Project Shooter with c++


#include "Components/SLWeaponsComponent.h"
#include "Weapon/SLBaseWeapon.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
USLWeaponsComponent::USLWeaponsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USLWeaponsComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	
}

void USLWeaponsComponent::StartFire()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->StartFire();
}
void USLWeaponsComponent::StopFire()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void USLWeaponsComponent::SpawnWeapon()
{
	if(!GetWorld() ) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	CurrentWeapon = GetWorld()->SpawnActor<ASLBaseWeapon>(WeaponClass);
	if(!CurrentWeapon) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(),AttachmentRules,WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);

}


