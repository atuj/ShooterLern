// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EvnQueryText_PickupCouldBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERLERN_API UEvnQueryText_PickupCouldBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()
public:
	UEvnQueryText_PickupCouldBeTaken(const FObjectInitializer& ObjectInitializer);
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	
};
