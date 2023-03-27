// Project Shooter with c++


#include "AI/Services/SLFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "SLUtils.h"
#include "Components/SLWeaponsComponent.h"

USLFireService::USLFireService()
{
	NodeName = "Fire";
}

void USLFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
	if(Controller)
	{
		const auto WeaponComponent = SLUtils::GetSLPlayerComponent<USLWeaponsComponent>(Controller->GetPawn());
		if(WeaponComponent)
		{
			HasAim?WeaponComponent->StartFire():WeaponComponent->StopFire();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}



