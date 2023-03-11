// Project Shooter with c++


#include "Pickups/SLHealthPickup.h"
#include "Components/SLHealthComponent.h"
#include "SLUtils.h"

bool ASLHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = SLUtils::GetSLPlayerComponent<USLHealthComponent>(PlayerPawn);
	if(!HealthComponent) return false;
	
	
	return HealthComponent->TryToAddHealth(HealthAmount);
}