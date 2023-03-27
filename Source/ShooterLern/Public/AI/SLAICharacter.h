// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "Player/SLBaseCharacter.h"
#include "SLAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SHOOTERLERN_API ASLAICharacter : public ASLBaseCharacter
{
	GENERATED_BODY()
public:
	ASLAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="AI")
	UBehaviorTree* BehaviorTreeAsset;

protected:
	virtual void OnDeath() override;
	
};
