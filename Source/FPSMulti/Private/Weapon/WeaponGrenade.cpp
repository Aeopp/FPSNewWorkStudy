// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/WeaponGrenade.h"
#include "Particles/ParticleSystemComponent.h"
#include "ConstructorHelpers.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components\SkeletalMeshComponent.h"
#include "Components\StaticMeshComponent.h"
#include "Engine\World.h"
#include "Character\FPSCharacterBase.h"
#include "Engine\Engine.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


AWeaponGrenade::AWeaponGrenade():Super()
{
	WeaponData.SKMeshPath = TEXT("SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/G67_Grenade/SK_G67.SK_G67'");
	WeaponData.SMMeshPath = TEXT("StaticMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/G67_Grenade/SM_G67.SM_G67'");
	WeaponData.ParticlePath = TEXT("ParticleSystem'/Game/Explosions/Particles/P_ImpactExplosion4.P_ImpactExplosion4'");

	GrenadeData.BoomSecond = 3.f;
	GrenadeData.GrenadePower = 200.f;
	WeaponData.Damage = 77.f;

	BoomParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Boom"));
	static auto SetParticle = ConstructorHelpers::FObjectFinder<UParticleSystem>(*WeaponData.ParticlePath);
	if (SetParticle.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("Constructor Grenade !! "));
		BoomParticle->SetTemplate(SetParticle.Object);
		BoomParticle->SetActive(false);
	}

	static auto SetSKMesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>(*WeaponData.SKMeshPath);
	static auto SetSMMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(*WeaponData.SMMeshPath);
	if (SetSKMesh.Succeeded())
		SKMeshComp->SetSkeletalMesh(SetSKMesh.Object);
	if (SetSMMesh.Succeeded())
		STMeshComp->SetStaticMesh(SetSMMesh.Object);
}
void AWeaponGrenade::BeginPlay()
{
	GetWorldTimerManager().SetTimer(BoomTimer, this, &AWeaponGrenade::Boom, GrenadeData.BoomSecond,false,
	GrenadeData.BoomSecond);
}

auto AWeaponGrenade::Boom() -> void
{
	BoomParticle->ActivateSystem();

	if (auto CurWorld = GetWorld() )
	{
		if (!IsPendingKill())
		{
			TArray<FOverlapResult> OUT OutOverlaps;

			FVector Center = GetActorLocation();

			FCollisionQueryParams IgnoreSelf;
			IgnoreSelf.AddIgnoredActor(this);
			
			if(CurWorld->OverlapMultiByObjectType(
				OUT OutOverlaps, Center,
				FQuat::Identity,
				FCollisionObjectQueryParams::DefaultObjectQueryParam,
				FCollisionShape::MakeSphere(GrenadeData.GrenadePower),
				IgnoreSelf))
			{
				for (const auto& Target : IN OutOverlaps)
				{
					if (auto Character = Cast<AFPSCharacterBase>(Target.GetActor()))
					{
							
						if (GEngine)
						{
						
							GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red,
								FString::Printf(TEXT("Character Hit!!")),
								false	, FVector2D::UnitVector*3.f);
						}
					}
				}
			}
		}
	}
	
	this->Destroy();
}



