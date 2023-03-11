// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	UNiagaraSystem* DefaultEffect;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "VFX")
	TMap<UPhysicalMaterial*, UNiagaraSystem*> EffectsMap;

		
};
