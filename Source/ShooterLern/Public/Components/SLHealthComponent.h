// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SLCoreTypes.h"
#include "SLHealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTERLERN_API USLHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USLHealthComponent();


	float GetHealth() const
	{
		return Health;
	}

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const
	{
		return FMath::IsNearlyZero(Health);
	}

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const
	{
		return Health / MaxHealth;
	}

	bool TryToAddHealth(float HealthAmount);
	bool IsHealthFull() const;


	FOnDeath OnDeath;
	FOnHealthChange OnHealthChange;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ClampMin="0.0", ClampMax="1000.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal")
	bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal", meta=(EditCondition = "AutoHeal"))
	float HealUpdateTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal", meta=(EditCondition = "AutoHeal"))
	float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal", meta=(EditCondition = "AutoHeal"))
	float HealModifier = 5.0f;


	virtual void BeginPlay() override;

private:
	float Health = 0.0f;

	FTimerHandle HealTimerHandle;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType,
	                     class AController* InstigatedBy, AActor* DamageCauser);


	void HealUpdate();

	void SetHealth(float NewHealth);
};
