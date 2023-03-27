// Project Shooter with c++


#include "Components/SLAIWeaponsComponent.h"
#include "Weapon/SLBaseWeapon.h"

void USLAIWeaponsComponent::StartFire()
{
	if(!CanFire()) return;

	if(CurrentWeapon->IsAmmoEmpty())
	{
		NextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}
}

void USLAIWeaponsComponent::NextWeapon()
{
	if(!CanEquip()) return;
	int32 NextIndex = (CurrentWeaponIndex+1)%Weapons.Num();

	while(NextIndex!= CurrentWeaponIndex)
	{
		if(!Weapons[NextIndex]->IsAmmoEmpty()) break;
		NextIndex = (NextIndex +1) % Weapons.Num();
	}
	if(CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
}




