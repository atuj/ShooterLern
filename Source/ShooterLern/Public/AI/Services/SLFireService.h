// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SLFireService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERLERN_API USLFireService : public UBTService
{
	GENERATED_BODY()
public:
	USLFireService();
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
