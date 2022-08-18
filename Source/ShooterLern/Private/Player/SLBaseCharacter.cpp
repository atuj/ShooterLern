// Project Shooter with c++


#include "Player/SLBaseCharacter.h"

#include "Camera/CameraAnim.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SLCharacterMovementComponent.h"
#include "Components/SLHealthComponent.h"
#include "Components/TextRenderComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCHaracterLog,All,All);

// Sets default values
ASLBaseCharacter::ASLBaseCharacter(const FObjectInitializer& ObjectInit):Super(ObjectInit.SetDefaultSubobjectClass<USLCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation= true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	HealthComponent = CreateDefaultSubobject<USLHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASLBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	
	
}

// Called every frame
void ASLBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto Health = HealthComponent->GetHealth();
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"),Health)));
	

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




