// Project Shooter with c++


#include "AI/Decorators/SLHealthPercentDecorator.h"
#include "AIController.h"
#include "SLUtils.h"
#include "Components/SLHealthComponent.h"
USLHealthPercentDecorator::USLHealthPercentDecorator()
{
	NodeName = "Health Percent";
}

bool USLHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;

	const auto HealthComponent = SLUtils::GetSLPlayerComponent<USLHealthComponent>(Controller->GetPawn());
	if(!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <=HealthPercent;
}

