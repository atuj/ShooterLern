// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "SLAIPerceptionComponent.generated.h"


UCLASS()
class SHOOTERLERN_API USLAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public:
	AActor* GetClosesEnemy() const;
	
};
