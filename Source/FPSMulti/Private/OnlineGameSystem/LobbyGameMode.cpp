// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\OnlineGameSystem\LobbyGameMode.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "FPSMultiGameInstance.h"
#include "FPSCharacterBase.h"

ALobbyGameMode::ALobbyGameMode() :AFPSMultiGameModeBase()
{
	FString PlayerPath = TEXT("Blueprint'/Game/Character/FPSCharacterBase_BP.FPSCharacterBase_BP_C'");

	static auto SetPlayer = ConstructorHelpers::FClassFinder<AFPSCharacterBase>
		(*PlayerPath);

	if (SetPlayer.Succeeded())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("%s"), *PlayerPath), false);
		}
		this->DefaultPawnClass = SetPlayer.Class;
	}
};

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	++NumberOfPlayers;

	if (NumberOfPlayers >= 2)
	{
		GetWorldTimerManager().
		SetTimer(GameStartTimer, this, &ALobbyGameMode::StartGame, 10);
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

void ALobbyGameMode::StartGame()
{
	auto GameInstance = Cast<UFPSMultiGameInstance>
		(GetGameInstance());

	if (GameInstance == nullptr)return;

	GameInstance->StartSession();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))return;

	bUseSeamlessTravel = true;
	World->ServerTravel("/Game/Maps/Game?listen");
}

