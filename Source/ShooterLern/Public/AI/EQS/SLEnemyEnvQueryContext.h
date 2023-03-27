// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "SLEnemyEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERLERN_API USLEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
public:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	FName EnemyActorKeyName = "EnemyActor";
	
};
