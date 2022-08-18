// Project Shooter with c++


#include "Components/SLCharacterMovementComponent.h"
#include"Player/SLBaseCharacter.h"

float USLCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASLBaseCharacter* Player = Cast<ASLBaseCharacter>(GetPawnOwner());
	
	return Player && Player->IsRunning()? MaxSpeed*RunModifire:MaxSpeed;
}