// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SLHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERLERN_API USLHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USLHealthComponent();

	
	
	float GetHealth() const
	{
		return Health;
	}

	UFUNCTION(BlueprintCallable)
	bool IsDead() const
	{
		 return Health <= 0.0f;
	}

	FOnDeath OnDeath;

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(ClampMin="0.0",ClampMax="1000.0"))
	float MaxHealth = 100.0f;
	
	virtual void BeginPlay() override;

private:
	float Health = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

		
};
