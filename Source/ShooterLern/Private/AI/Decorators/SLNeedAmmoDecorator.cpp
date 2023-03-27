// Project Shooter with c++


#include "AI/Decorators/SLNeedAmmoDecorator.h"
#include "AIController.h"
#include "SLUtils.h"
#include "Components/SLWeaponsComponent.h"

USLNeedAmmoDecorator::USLNeedAmmoDecorator()
{
	NodeName = "Need Ammo";
}

bool USLNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;

	const auto WeaponComponent = SLUtils::GetSLPlayerComponent<USLWeaponsComponent>(Controller->GetPawn());
	if(!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponType);
	
}



