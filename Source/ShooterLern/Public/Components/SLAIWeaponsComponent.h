// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "Components/SLWeaponsComponent.h"
#include "SLAIWeaponsComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERLERN_API USLAIWeaponsComponent : public USLWeaponsComponent
{
	GENERATED_BODY()
public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
	
	
};
