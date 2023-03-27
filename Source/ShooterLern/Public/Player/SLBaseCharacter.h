// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTestingManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SLBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USLHealthComponent;
class UTextRenderComponent;
class USLWeaponsComponent;

UCLASS()
class SHOOTERLERN_API ASLBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASLBaseCharacter(const FObjectInitializer& ObjectInit);

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	USLHealthComponent* HealthComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	USLWeaponsComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D LandedDamage = FVector2D(10.0f,100.0f);
	

	
	
	
	virtual void BeginPlay() override;
	
	virtual void OnDeath();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category="Movement")
	float GetMovementDirection() const;
	

private:

	bool WantsToRun = false;
	bool IsMovingForward = false;
	
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void LookUp(float Amount);
	void TurnAround(float Amount);

	void OnStartRunning();
	void OnStopRunning();

	
	void OnHealthChange(float Health, float HealthDelta);


	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);


	
	
};
