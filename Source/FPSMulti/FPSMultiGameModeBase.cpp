// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSMultiGameModeBase.h"
#include "ConstructorHelpers.h"
#include "FPSMulti\Public\Character\FPSCharacterBase.h"
#include "Engine\Engine.h"
AFPSMultiGameModeBase::AFPSMultiGameModeBase()
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
}