// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SLBaseWeapon.generated.h"



class USkeletalMeshComponent;

UCLASS()
class SHOOTERLERN_API ASLBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ASLBaseWeapon();


	virtual void StopFire();
	virtual void StartFire();
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MuzzleSocket")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MuzzleSocket")
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DamageAmount = 10.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimerBetweenShots = 0.02f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float BulletSprad = 1.5f;
	
	virtual void BeginPlay() override;

	void MakeShot();
	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd );
	void MakeDamage(const FHitResult& HitResult);
private:
	FTimerHandle ShotTimerHandle;
};
