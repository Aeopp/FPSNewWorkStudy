// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacterBase.h"

#include "UnrealNetwork.h"

#include "ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Components/InputComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AFPSCharacterBase::AFPSCharacterBase() {
	SetReplicates(true);

	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKMeshObject(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SKMeshObject.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SKMeshObject.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	MoveForwardSpeed = 60.0f;
	MoveRightSpeed = 30.0f;
}

void AFPSCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSCharacterBase, MoveForwardVal);
	DOREPLIFETIME(AFPSCharacterBase, MoveRightVal);
	DOREPLIFETIME(AFPSCharacterBase, TurnRate);
	DOREPLIFETIME(AFPSCharacterBase, AimPitch);
}

void AFPSCharacterBase::BeginPlay() {
	Super::BeginPlay();
	
}

void AFPSCharacterBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AFPSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacterBase::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacterBase::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacterBase::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacterBase::StopJumping);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacterBase::Fire);
}

void AFPSCharacterBase::Jump() {
	Super::Jump();
}

void AFPSCharacterBase::StopJumping() {
	Super::StopJumping();
}

void AFPSCharacterBase::ServerMoveForward_Implementation(float AxisValue) {
	MoveForwardVal = MoveForwardSpeed * AxisValue * UGameplayStatics::GetWorldDeltaSeconds(this);
}

void AFPSCharacterBase::MoveForward(float AxisValue) {
	ServerMoveForward(AxisValue);

	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));

	AddMovementInput(ForwardVector, MoveForwardVal);
}

void AFPSCharacterBase::ServerMoveRight_Implementation(float AxisValue) {
	MoveRightVal = MoveRightSpeed * AxisValue * UGameplayStatics::GetWorldDeltaSeconds(this);
}

void AFPSCharacterBase::MoveRight(float AxisValue) {
	ServerMoveRight(AxisValue);

	FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));

	AddMovementInput(RightVector, MoveRightVal);
}

void AFPSCharacterBase::ServerTurn_Implementation(float AxisValue) {
	TurnRate = AxisValue;
}

void AFPSCharacterBase::Turn(float AxisValue) {
	ServerTurn(AxisValue);
	
	AddControllerYawInput(AxisValue);
}

void AFPSCharacterBase::ServerLookUp_Implementation(float AxisValue) {
	auto ControlRot = GetControlRotation();
	auto ActRot = GetActorRotation();

	AimPitch = UKismetMathLibrary::ClampAngle(ControlRot.Pitch - ActRot.Pitch, -90.0f, 90.0f);
}

void AFPSCharacterBase::LookUp(float AxisValue) {
	LookUpRate = AxisValue;
	ServerLookUp(AxisValue);

	AddControllerPitchInput(AxisValue);
}

void AFPSCharacterBase::Fire() {
	auto Loc = GetMesh()->GetSocketLocation(TEXT("head"));

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ ObjectTypeQuery3 };
	FHitResult HitRes;
	UKismetSystemLibrary::LineTraceSingleForObjects(this, Loc, Loc + GetActorForwardVector() * 1000.0f, ObjectTypes, false, { nullptr }, EDrawDebugTrace::ForDuration, HitRes, true);
}