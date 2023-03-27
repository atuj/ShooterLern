// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SLAIController.generated.h"

class USLAIPerceptionComponent;

UCLASS()
class SHOOTERLERN_API ASLAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASLAIController();

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Components")
	USLAIPerceptionComponent* SLAIPerceptionComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AI")
	FName FocusOnKeyName = "EnemyActor";
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	AActor* GetFocusOnActor() const;
};
