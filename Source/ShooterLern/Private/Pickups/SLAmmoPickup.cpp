// Project Shooter with c++


#include "Pickups/SLAmmoPickup.h"
#include "Components/SLHealthComponent.h"
#include "Components/SLWeaponsComponent.h"
#include "SLUtils.h"

bool ASLAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = SLUtils::GetSLPlayerComponent<USLHealthComponent>(PlayerPawn);
	if(!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = SLUtils::GetSLPlayerComponent<USLWeaponsComponent>(PlayerPawn);
	if(!WeaponComponent ) return false;
	
	
	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
