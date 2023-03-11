// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SLBasePickup.h"
#include "SLAmmoPickup.generated.h"

class ASLBaseWeapon;

UCLASS()
class SHOOTERLERN_API ASLAmmoPickup : public ASLBasePickup
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup",meta = (ClampMin = "1.0", ClampMax="10.0"))
	int32 ClipsAmount = 10;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	TSubclassOf<ASLBaseWeapon> WeaponType;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
	
};
