// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacterAnimInstance.h"
#include "FPSCharacterBase.h"

#include "UnrealNetwork.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UFPSCharacterAnimInstance::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();

	OwningCharacter = Cast<AFPSCharacterBase>(TryGetPawnOwner());
}

void UFPSCharacterAnimInstance::NativeUpdateAnimation(float DeltaTimeX) {
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (OwningCharacter) {
		SetInAirState();
		SetSpeeds();
		SetValues();
	}
}

void UFPSCharacterAnimInstance::SetInAirState() {
	bIsInAir = OwningCharacter->GetMovementComponent()->IsFalling();
}

void UFPSCharacterAnimInstance::SetSpeeds() {
	MoveForwardSpeed = OwningCharacter->MoveForwardSpeed;
	MoveRightSpeed = OwningCharacter->MoveRightSpeed;
}

void UFPSCharacterAnimInstance::SetValues() {
	MoveForwardVal = OwningCharacter->MoveForwardVal;
	MoveRightVal = OwningCharacter->MoveRightVal;
	TurnRate = OwningCharacter->TurnRate;
	AimPitch = OwningCharacter->AimPitch;
}