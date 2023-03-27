// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SLBasePickup.generated.h"


class USphereComponent;

UCLASS()
class SHOOTERLERN_API ASLBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASLBasePickup();

	

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	float RespawnTime = 5.0f;
	
	virtual void BeginPlay() override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	virtual void Tick(float DeltaTime) override;
	bool CouldBeTaken() const;

private:
	float RotationYaw = 0.0f;
	FTimerHandle RespawnTimerHandle;
	
	virtual bool GivePickupTo(APawn* PlayerPawn);
	void PickupWasTaken();
	void Respawn();
	
	void GenerateRotationYaw();
};
