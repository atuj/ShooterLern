// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SLBaseWeapon.h"
#include "SLRifleWeaponBase.generated.h"


class USLWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	FString TraceTargetName = "TraceTarget";
	

	UPROPERTY(VisibleAnywhere, Category="VFX")
	USLWeaponFXComponent* WeaponFXComponent;

	virtual void BeginPlay() override;
	
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;
	
	void MakeDamage(const FHitResult& HitResult);
	void InitMuzzleFX();
	void SetMuzzleFXVisibility(bool Visibility);
	void SpawnTraceFX(const FVector& TraceStart,const FVector& TraceEnd);
};
