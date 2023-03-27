// Project Shooter with c++


#include "SLGameModeBase.h"
#include "Player/SLBaseCharacter.h"
#include "Player/SLPlayerController.h"
#include "UI/SLGameHUD.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogSLGameModeBase,All,All)

ASLGameModeBase::ASLGameModeBase()
{
	DefaultPawnClass = ASLBaseCharacter::StaticClass();
	PlayerControllerClass = ASLPlayerController::StaticClass();
	HUDClass = ASLGameHUD::StaticClass();
	
}

void ASLGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CurrentRound = 1;
	StartRound();
}

void ASLGameModeBase::SpawnBots()
{
	if(!GetWorld()) return;
	for(int32 i = 0; i< GameData.PlayersNum-1;i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto SLAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass,SpawnInfo);
		RestartPlayer(SLAIController);
	}
}

UClass* ASLGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if(InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASLGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundsTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle,this,&ASLGameModeBase::GameTimerUpdate,1.0f,true);
}

void ASLGameModeBase::GameTimerUpdate()
{
	UE_LOG(LogSLGameModeBase,Display,TEXT("Time: %i / Round: %i/%i"),RoundCountDown,CurrentRound,GameData.RoundsNum);

	if(--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
		if(CurrentRound +1 <=GameData.RoundsNum)
		{
			++CurrentRound;
			StartRound();
			ResetPlayers();
		}
		else
		{
			UE_LOG(LogSLGameModeBase,Display,TEXT("============= GAME OVER ============="))
		}
	}
}

void ASLGameModeBase::ResetPlayers()
{
	if(!GetWorld()) return;
	for(auto It = GetWorld()->GetControllerIterator();It;++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void ASLGameModeBase::ResetOnePlayer(AController* Controller)
{
	if(Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
}

































