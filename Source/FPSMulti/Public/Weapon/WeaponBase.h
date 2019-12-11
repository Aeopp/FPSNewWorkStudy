// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

USTRUCT(BlueprintType,Blueprintable)
struct FWeaponData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float Damage = 10.7f;
	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	FString SKMeshPath;
	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	FString SMMeshPath;
	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	FString ParticlePath;
};

UCLASS()
class FPSMULTI_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();


	

public:	
	
protected:
	UPROPERTY()
	FWeaponData WeaponData;
	UPROPERTY()
	class UStaticMeshComponent* STMeshComp;
	UPROPERTY()
	class USkeletalMeshComponent* SKMeshComp;
};
