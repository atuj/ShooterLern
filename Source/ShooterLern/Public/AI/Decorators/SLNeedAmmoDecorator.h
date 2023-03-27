// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SLNeedAmmoDecorator.generated.h"

class ASLBaseWeapon;

UCLASS()
class SHOOTERLERN_API USLNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	USLNeedAmmoDecorator();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	TSubclassOf<ASLBaseWeapon> WeaponType;
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
