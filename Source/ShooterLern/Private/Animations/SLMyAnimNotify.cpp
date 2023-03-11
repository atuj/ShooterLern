// Project Shooter with c++


#include "Animations/SLMyAnimNotify.h"

void USLMyAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp,Animation);
}