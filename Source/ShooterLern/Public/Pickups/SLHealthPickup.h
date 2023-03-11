// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SLBasePickup.h"
#include "SLHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERLERN_API ASLHealthPickup : public ASLBasePickup
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Pickup",meta = (ClampMin = "1", ClampMax = "100"))
	float HealthAmount = 100;
	
private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
	
};
