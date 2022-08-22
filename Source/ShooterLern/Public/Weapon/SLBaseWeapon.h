// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SLBaseWeapon.generated.h"



class USkeletalMeshComponent;

UCLASS()
class SHOOTERLERN_API ASLBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ASLBaseWeapon();


	virtual void Fire();
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USkeletalMeshComponent* WeaponMesh;

	virtual void BeginPlay() override;

	
};
