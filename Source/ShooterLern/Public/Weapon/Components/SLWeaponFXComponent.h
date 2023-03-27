// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SLCoreTypes.h"
#include "SLWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERLERN_API USLWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USLWeaponFXComponent();

	void PlayImpactFX(const FHitResult& hit);

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "VFX")
	FImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "VFX")
	TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;

		
};
