// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SLBaseWeapon.h"
#include "SLRifleWeaponBase.generated.h"


class USLWeaponFXComponent;

UCLASS()
class SHOOTERLERN_API ASLRifleWeaponBase : public ASLBaseWeapon
{
	GENERATED_BODY()
public:

	ASLRifleWeaponBase();

	virtual void StopFire() override;
	virtual void StartFire() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TimerBetweenShots = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float BulletSprad = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float DamageAmount = 10.0f;

	UPROPERTY(VisibleAnywhere, Category="VFX")
	USLWeaponFXComponent* WeaponFXComponent;

	virtual void BeginPlay() override;
	
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
private:
	FTimerHandle ShotTimerHandle;

	void MakeDamage(const FHitResult& HitResult);
};
