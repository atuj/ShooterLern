// Project Shooter with c++


#include "SLGameModeBase.h"
#include "Player/SLBaseCharacter.h"
#include "Player/SLPlayerController.h"
#include "UI/SLGameHUD.h"

ASLGameModeBase::ASLGameModeBase()
{
	DefaultPawnClass = ASLBaseCharacter::StaticClass();
	PlayerControllerClass = ASLPlayerController::StaticClass();
	HUDClass = ASLGameHUD::StaticClass();
	
}
