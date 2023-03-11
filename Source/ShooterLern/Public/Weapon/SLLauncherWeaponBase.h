// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SLBaseWeapon.h"
#include "SLLauncherWeaponBase.generated.h"

class ASLProjectile;

UCLASS()
class SHOOTERLERN_API ASLLauncherWeaponBase : public ASLBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ASLProjectile> ProjectileClass;

	virtual void MakeShot() override;
};
