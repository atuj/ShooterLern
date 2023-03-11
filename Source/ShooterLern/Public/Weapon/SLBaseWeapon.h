// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SLCoreTypes.h"
#include "SLBaseWeapon.generated.h"


class USkeletalMeshComponent;


UCLASS()
class SHOOTERLERN_API ASLBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	ASLBaseWeapon();

	FOnClipEmptySignature OnClipEmpty;

	virtual void StopFire();
	virtual void StartFire();

	void ChangeClip();
	bool CanReload() const;

	FWeaponUIData GetUIData() const { return UIData; }
	FAmmoData GetAmmoData() const { return CurrentAmmo; }

	bool TryToAddAmmo(int32 ClipsAmount);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FAmmoData DefaultAmmo{15, 10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	FWeaponUIData UIData;

	virtual void BeginPlay() override;

	virtual void MakeShot();
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipsEmpty() const;
	bool IsAmmoFull() const;

	void LogAmmo();

private:
	FAmmoData CurrentAmmo;
};
