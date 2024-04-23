// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"

#include "InputActionValue.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FPSCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FPSCam->SetupAttachment(GetMesh());
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
	UE_LOG(LogTemp,Warning,TEXT("Move"));
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
	UE_LOG(LogTemp,Warning,TEXT("Look"));
	const FVector2D LookValue = Value.Get<FVector2D>();
 
	if (LookValue.X != 0.f)
	{
		AddControllerYawInput(LookValue.X);
	}
 
	if (LookValue.Y != 0.f)
	{
		AddControllerPitchInput(LookValue.Y);
	}
}

void APlayerChar::Shoot(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("Shoot"));
}



