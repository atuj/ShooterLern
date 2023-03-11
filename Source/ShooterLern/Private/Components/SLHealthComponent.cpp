// Project Shooter with c++


#include "Components/SLHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"


DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog,All,All);

USLHealthComponent::USLHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}



void USLHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);
	
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USLHealthComponent::OnTakeAnyDamage);
	}
	
}

void USLHealthComponent::OnTakeAnyDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{

	if(Damage <=0.0f || IsDead() || !GetWorld()) return;
	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	
	if(IsDead())
	{
		 OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle,this,&USLHealthComponent::HealUpdate, HealUpdateTime,true,HealDelay);
	}
	
}

void USLHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if(IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USLHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChange.Broadcast(Health);
}

bool USLHealthComponent::TryToAddHealth(float HealthAmount)
{
	if(IsDead() || IsHealthFull()) return false;
	SetHealth(Health+HealthAmount);
	return true;
}

bool USLHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health,MaxHealth);
}


