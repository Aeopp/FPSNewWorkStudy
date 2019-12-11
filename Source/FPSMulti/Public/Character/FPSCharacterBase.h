// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacterBase.generated.h"

UCLASS()
class FPSMULTI_API AFPSCharacterBase : public ACharacter {
	GENERATED_BODY()

public:
	AFPSCharacterBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	virtual void StopJumping() override;

private:
	UFUNCTION(Server, Reliable)
	void ServerMoveForward(float AxisValue);
	void MoveForward(float AxisValue);
	UFUNCTION(Server, Reliable)
	void ServerMoveRight(float AxisValue);
	void MoveRight(float AxisValue);
	UFUNCTION(Server, Reliable)
	void ServerTurn(float AxisValue);
	void Turn(float AxisValue);
	UFUNCTION(Server, Reliable)
	void ServerLookUp(float AxisValue);
	void LookUp(float AxisValue);

	void Fire();

public:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float LookUpRate;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float AimPitch;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float MoveForwardVal;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float MoveRightVal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float MoveForwardSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float MoveRightSpeed;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = true))
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = true))
	class UCameraComponent* Camera;
};
