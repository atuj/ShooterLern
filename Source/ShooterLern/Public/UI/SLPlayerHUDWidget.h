// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLCoreTypes.h"
#include "SLPlayerHUDWidget.generated.h"

UCLASS()
class SHOOTERLERN_API USLPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Category = "UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable,Category = "UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable,Category = "UI")
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable,Category = "UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable,Category = "UI")
	bool IsPlayerSpectating() const;
	
};
