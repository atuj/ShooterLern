// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SLCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERLERN_API USLCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Movement",meta=(ClampMin="1.5",ClampMax="10.0"))
	float RunModifire = 2.0f;
	
	virtual float GetMaxSpeed() const override;
	
};
