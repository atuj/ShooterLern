// Project Shooter with c++


#include "UI/SLPlayerHUDWidget.h"
#include "Components/SLHealthComponent.h"
#include "Components/SLWeaponsComponent.h"
#include "SLUtils.h"

float USLPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent =SLUtils::GetSLPlayerComponent<USLHealthComponent>(GetOwningPlayerPawn());
	if(!HealthComponent) return 0.0f;
	return HealthComponent->GetHealthPercent();
}

bool USLPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = SLUtils::GetSLPlayerComponent<USLWeaponsComponent>(GetOwningPlayerPawn());
	if(!WeaponComponent) return false;
	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USLPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = SLUtils::GetSLPlayerComponent<USLWeaponsComponent>(GetOwningPlayerPawn());
	if(!WeaponComponent) return false;
	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool USLPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent =SLUtils::GetSLPlayerComponent<USLHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool USLPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool USLPlayerHUDWidget::Initialize()
{

	const auto HealthComponent =SLUtils::GetSLPlayerComponent<USLHealthComponent>(GetOwningPlayerPawn());
	if(HealthComponent)
	{
		HealthComponent->OnHealthChange.AddUObject(this,&USLPlayerHUDWidget::OnHealthChanged);
	}
	return Super::Initialize();
}

void USLPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if(HealthDelta < 0)
	{
		OnTakeDamage();
	}
	
}



