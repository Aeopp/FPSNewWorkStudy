// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuWidget.h"


#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MainMenu.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "FPSMultiGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPSMULTI_API UFPSMultiGameInstance : 
public UGameInstance,
public IMenuInterface
{
	GENERATED_BODY()
public:
	UFPSMultiGameInstance(const FObjectInitializer & ObjectInitializer);
	virtual void Init();

	UFUNCTION(BlueprintCallable)
		void LoadMenuWidget();
	UFUNCTION(BlueprintCallable)
		void InGameLoadMenu();

	void StartSession();


	UFUNCTION(Exec)
	virtual void Host(FString ServerName)override;
	UFUNCTION(Exec)
	virtual void Join(uint32 Index)override;
	virtual void LoadMainMenu()override;
	void RefreshServerList() override;

private:
	TSubclassOf<class UUserWidget>MenuClass;
	TSubclassOf<class UUserWidget>InGameMenuClass;

	UMainMenu* Menu;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnCreateSessionComplete(FName SessionName,
		bool Success);
	void OnDestroySessionComplete(FName SessionName,
		bool Success);
	void OnFindSessionsComplete(bool Success);
	void OnJoinSessionComplete(FName SessionName,
	EOnJoinSessionCompleteResult::Type Result);

	FString DesiredServerName;
	void CreateSession();
};
