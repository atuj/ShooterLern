// Project Shooter with c++


#include "Pickups/SLBasePickup.h"
#include "Components/SphereComponent.h"

ASLBasePickup::ASLBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);

}


void ASLBasePickup::BeginPlay()
{
	Super::BeginPlay();

	check(CollisionComponent);

	GenerateRotationYaw();
	
}


void ASLBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f,RotationYaw,0.0f));

}

void ASLBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if(GivePickupTo(Pawn))
	{
		PickupWasTaken();
	}
}

void ASLBasePickup::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);
	if(GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false,true);
	}
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle,this,&ASLBasePickup::Respawn,RespawnTime);
}

void  ASLBasePickup::Respawn()
{
	GenerateRotationYaw();
	CollisionComponent->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);
	if(GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true,true);
	}
}

bool ASLBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void ASLBasePickup::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool()?1.0f:-1.0f;
	RotationYaw = FMath::RandRange(1.0f,2.0f)*Direction;
}

