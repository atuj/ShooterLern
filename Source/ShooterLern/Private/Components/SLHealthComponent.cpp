// Project Shooter with c++


#include "Components/SLHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Dev/SLFireDamageType.h"
#include "Dev/SLIceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog,All,All);

USLHealthComponent::USLHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}



void USLHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USLHealthComponent::OnTakeAnyDamage);
	}
	
}

void USLHealthComponent::OnTakeAnyDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	UE_LOG(HealthComponentLog, Display, TEXT("Damage: %f"),Damage);

	if(DamageType)
	{
		if(DamageType->IsA<USLFireDamageType>())
		{
			UE_LOG(HealthComponentLog, Display, TEXT("Fire damage"));
		}
		else if (DamageType -> IsA<USLIceDamageType>())
		{
			UE_LOG(HealthComponentLog, Display, TEXT("Ice damage"));
		}
	}
}

