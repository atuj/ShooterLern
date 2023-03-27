// Project Shooter with c++


#include "AI/EQS/EvnQueryText_PickupCouldBeTaken.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/SLBasePickup.h"

UEvnQueryText_PickupCouldBeTaken::UEvnQueryText_PickupCouldBeTaken(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEvnQueryText_PickupCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{

	const auto DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner,QueryInstance.QueryID);
	const bool WantsBeTakable = BoolValue.GetValue();
	
	for( FEnvQueryInstance::ItemIterator It(this,QueryInstance);It;++It)
	{
		AActor* ItemActor = GetItemActor(QueryInstance,It.GetIndex());
		const auto PickupActor = Cast<ASLBasePickup>(ItemActor);
		if(!PickupActor) continue;
		const auto CouldBeTaken = PickupActor->CouldBeTaken();
		It.SetScore(TestPurpose,FilterType,CouldBeTaken,true);
	}
}


















