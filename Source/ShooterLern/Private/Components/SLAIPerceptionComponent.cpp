// Project Shooter with c++


#include "Components/SLAIPerceptionComponent.h"
#include "AIController.h"
#include "SLUtils.h"
#include "Components/SLHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USLAIPerceptionComponent::GetClosesEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(),PercieveActors);
	if(PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if(!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return nullptr;
	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PercieveActor: PercieveActors)
	{
		const auto HealthComponent = SLUtils::GetSLPlayerComponent<USLHealthComponent>(PercieveActor);
		if(HealthComponent && !HealthComponent->IsDead()) // check if enemies or no
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if(CurrentDistance<BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}
		}
	}
	return BestPawn;
}


