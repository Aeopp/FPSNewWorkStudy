// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSMultiGameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPSMULTI_API ALobbyGameMode : 
	public AFPSMultiGameModeBase
{
	GENERATED_BODY()

public:
	ALobbyGameMode();
	void PostLogin(APlayerController* NewPlayer) override;
	void Logout(AController* Exiting) override;
private:
	void StartGame();
	uint32 NumberOfPlayers = 0;
	FTimerHandle GameStartTimer;
};
