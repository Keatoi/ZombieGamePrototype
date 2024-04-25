// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"

#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Spawn camera at eye height
	FPSCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	check(FPSCam != nullptr);
	FPSCam->SetRelativeLocation(FVector(0.f,0.f,BaseEyeHeight));
	FPSCam->SetupAttachment(GetCapsuleComponent());
	//Create FPS Arms mesh and set to only be seen by its player
	FPSArms_SK = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPS ARMS"));
	check(FPSArms_SK != nullptr);
	FPSArms_SK->SetOnlyOwnerSee(true);
	FPSArms_SK->SetupAttachment(FPSCam);
	//Disable Shadows
	FPSArms_SK->bCastDynamicShadow = false;
	FPSArms_SK->CastShadow = false;
	bInvertControls = false;
}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerChar::Move(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp,Warning,TEXT("Move"));
	const FVector2D MoveValue = Value.Get<FVector2D>();
	const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);
 
	// Forward/Backward direction
	if (MoveValue.Y != 0.f)
	{
		// Get forward vector
		const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
 
		AddMovementInput(Direction, MoveValue.Y);
	}
 
	// Right/Left direction
	if (MoveValue.X != 0.f)
	{
		// Get right vector
		const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);
 
		AddMovementInput(Direction, MoveValue.X);
	}
}

void APlayerChar::Look(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp,Warning,TEXT("Look"));
	const FVector2D LookValue = Value.Get<FVector2D>();
 
	if (LookValue.X != 0.f)
	{
		AddControllerYawInput(LookValue.X);
	}
 
	if (LookValue.Y != 0.f)
	{
		if(bInvertControls) AddControllerPitchInput(LookValue.Y);
		else AddControllerPitchInput(-LookValue.Y);
	}
}

void APlayerChar::Shoot(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("Shoot"));
}



