// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SLWeaponsComponent.generated.h"

class ASLBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERLERN_API USLWeaponsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USLWeaponsComponent();
	void StartFire();
	void StopFire();
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASLBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";

private:

	UPROPERTY()
	ASLBaseWeapon* CurrentWeapon = nullptr;
	void SpawnWeapon();
		
};
