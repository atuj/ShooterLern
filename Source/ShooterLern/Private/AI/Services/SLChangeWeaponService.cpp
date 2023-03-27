// Project Shooter with c++


#include "AI/Services/SLChangeWeaponService.h"
#include "Components/SLWeaponsComponent.h"
#include "AIController.h"
#include "SLUtils.h"

USLChangeWeaponService::USLChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void USLChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(Controller)
	{
		const auto WeaponComponent = SLUtils::GetSLPlayerComponent<USLWeaponsComponent>(Controller->GetPawn());
		if(WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

