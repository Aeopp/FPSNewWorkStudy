// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "WeaponGrenade.generated.h"

/**
 * 
 */

UCLASS()
class FPSMULTI_API AWeaponGrenade : public AWeaponBase
{
	GENERATED_BODY()
public:
	
	AWeaponGrenade();
	UPROPERTY()
	class UParticleSystemComponent* BoomParticle;

	UFUNCTION()
	void Boom();
protected:
	virtual void BeginPlay()override;
private:
	FTimerHandle BoomTimer;

	struct FGrenadeData
	{float BoomSecond=3.f;float GrenadePower=200.f;};

	FGrenadeData GrenadeData;
};
