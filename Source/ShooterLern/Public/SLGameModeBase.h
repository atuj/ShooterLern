// Project Shooter with c++

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SLCoreTypes.h"
#include "SLGameModeBase.generated.h"


class AAIController;

UCLASS()
class SHOOTERLERN_API ASLGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASLGameModeBase();

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	
protected:
	UPROPERTY(EditDefaultsOnly,Category="Game")
	TSubclassOf<APawn> AIPawnClass;
	
	UPROPERTY(EditDefaultsOnly,Category="Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly,Category="Game")
	FGameData GameData;
private:
	int32 CurrentRound = 1;
	int32 RoundCountDown = 0;
	FTimerHandle GameRoundTimerHandle;

	void StartRound();
	void GameTimerUpdate();
	void SpawnBots();

	void ResetPlayers();
	void ResetOnePlayer(AController* Controller);
	
};

















