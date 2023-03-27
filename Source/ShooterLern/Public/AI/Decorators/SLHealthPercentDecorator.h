// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SLHealthPercentDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERLERN_API USLHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	USLHealthPercentDecorator();
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	float HealthPercent = 0.6f;
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	
};
