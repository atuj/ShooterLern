// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SLFindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERLERN_API USLFindEnemyService : public UBTService
{
	GENERATED_BODY()
public:
	USLFindEnemyService();
protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
