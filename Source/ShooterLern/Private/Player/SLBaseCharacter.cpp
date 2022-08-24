// Project Shooter with c++


#include "Player/SLBaseCharacter.h"
#include "Player/SLBaseCharacter.h"
#include "Player/SLBaseCharacter.h"

#include "Camera/CameraAnim.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SLCharacterMovementComponent.h"
#include "Components/SLHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "Components/SLWeaponsComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter,All,All);

// Sets default values
ASLBaseCharacter::ASLBaseCharacter(const FObjectInitializer& ObjectInit):Super(ObjectInit.SetDefaultSubobjectClass<USLCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation= true;
	SpringArmComponent->SocketOffset = FVector(0.0f,100.0f,80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	HealthComponent = CreateDefaultSubobject<USLHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<USLWeaponsComponent>("WeaponComponent");

}

// Called when the game starts or when spawned
void ASLBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());

	OnHealthChange(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &ASLBaseCharacter::OnDeath);
	HealthComponent->OnHealthChange.AddUObject(this, &ASLBaseCharacter::OnHealthChange);

	LandedDelegate.AddDynamic(this, &ASLBaseCharacter::OnGroundLanded);


}

void ASLBaseCharacter::OnHealthChange(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"),Health)));
}


// Called every frame
void ASLBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TakeDamage(0.05f,FDamageEvent {}, Controller, this);

	

}

// Called to bind functionality to input
void ASLBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ASLBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASLBaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp",this,&ASLBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround",this,&ASLBaseCharacter::TurnAround);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ASLBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run",IE_Pressed,this,&ASLBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run",IE_Released,this,&ASLBaseCharacter::OnStopRunning);

	PlayerInputComponent->BindAction("Fire",IE_Pressed, WeaponComponent, &USLWeaponsComponent::Fire);
	

}




void ASLBaseCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	if(Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(),Amount);
}


void ASLBaseCharacter::MoveRight(float Amount)
{
	if(Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(),Amount);
}

void ASLBaseCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void ASLBaseCharacter::TurnAround(float Amount)
{
	AddControllerYawInput(Amount);
}

void ASLBaseCharacter::OnStartRunning()
{

	WantsToRun = true;
}

void ASLBaseCharacter::OnStopRunning()
{
	WantsToRun = false;
}

bool ASLBaseCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float ASLBaseCharacter::GetMovementDirection() const
{
	if(GetVelocity().IsZero()) return 0.0f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(),VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero()? Degrees: Degrees *FMath::Sign(CrossProduct.Z);
}

void ASLBaseCharacter::OnDeath()
{
	UE_LOG(LogBaseCharacter, Display, TEXT("Player %s is death"), *GetName());

	PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);

	if(Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	GetCapsuleComponent()->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);
}

void ASLBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;

	if(FallVelocityZ < LandedDamageVelocity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity,LandedDamage,FallVelocityZ);
	TakeDamage(FinalDamage, FDamageEvent{},nullptr,nullptr);
}




