// Project Shooter with c++


#include "AI/SLAIController.h"
#include "AI/SLAICharacter.h"
#include "Components/SLAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void ASLAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto SLCharacter = Cast<ASLAICharacter>(InPawn);
	if(SLCharacter)
	{
		RunBehaviorTree(SLCharacter->BehaviorTreeAsset);
	}
}

ASLAIController::ASLAIController()
{
	SLAIPerceptionComponent = CreateDefaultSubobject<USLAIPerceptionComponent>("SLPerceptionComponent");
	SetPerceptionComponent(*SLAIPerceptionComponent);

	bWantsPlayerState = true;
}

void ASLAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* ASLAIController::GetFocusOnActor() const
{
	if(!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}

