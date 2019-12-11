// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPSCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPSMULTI_API UFPSCharacterAnimInstance : public UAnimInstance {
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterState)
	bool bIsInAir;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterState)
	float MoveForwardSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterState)
	float MoveRightSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterState)
	float MoveForwardVal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterState)
	float MoveRightVal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterState)
	float TurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterState)
	float AimPitch;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterState)
	float AimYaw;

private:
	void SetInAirState();
	void SetSpeeds();
	void SetValues();

private:
	UPROPERTY()
	class AFPSCharacterBase* OwningCharacter;
};
