// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

class FPSMULTI_API IMenuInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Host(FString ServerName) = 0;
	virtual void Join(uint32 Index) = 0;
	virtual void LoadMainMenu() = 0;
	virtual void RefreshServerList() = 0;
};


/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class FPSMULTI_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Setup();
	void Teardown();
	void SetMenuInterface(IMenuInterface* MenuInterface);
protected:
	IMenuInterface* MenuInterface;
};
