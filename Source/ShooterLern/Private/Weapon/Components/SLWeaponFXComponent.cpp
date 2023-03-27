// Project Shooter with c++


#include "Weapon/Components/SLWeaponFXComponent.h"
//#include "NiagaraFunctionLibrary.h"
#include "..\..\..\..\..\UE5\UE_5.0\Engine\Plugins\FX\Niagara\Source\Niagara\Public\NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

USLWeaponFXComponent::USLWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USLWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;

	if(Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if(ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap[PhysMat];
		}
	}

	// niagara
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect, Hit.Location, Hit.ImpactPoint.Rotation());

	// decal
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),ImpactData.DecalData.Material,ImpactData.DecalData.Size, Hit.ImpactPoint, FRotator(90.0f,0.0f,0.0f));
	if(DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}

}
