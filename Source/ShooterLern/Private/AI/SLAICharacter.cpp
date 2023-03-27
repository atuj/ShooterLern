// Project Shooter with c++


#include "AI/SLAICharacter.h"
#include "AI/SLAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SLAIWeaponsComponent.h"
#include "BrainComponent.h"

ASLAICharacter::ASLAICharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USLAIWeaponsComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ASLAIController::StaticClass();
	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void ASLAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto SLController = Cast<AAIController>(Controller);
	if(SLController && SLController->BrainComponent)
	{
		SLController->BrainComponent->Cleanup();
	}
}

