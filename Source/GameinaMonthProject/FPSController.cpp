// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSController.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputAction.h"
#include "PlayerChar.h"

AFPSController::AFPSController()
{
}

void AFPSController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = Cast<APlayerChar>(GetPawn());
	UE_LOG(LogTemp,Warning,TEXT("PC activated"));
	/* Add input mapping context */
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AFPSController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AFPSController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent))
	{
		UE_LOG(LogTemp,Warning,TEXT("Input Called"));
		Input->BindAction(InputMove,ETriggerEvent::Triggered,this,&AFPSController::CallMove);
		Input->BindAction(InputLook,ETriggerEvent::Triggered,this,&AFPSController::CallLook);
		Input->BindAction(InputShoot,ETriggerEvent::Triggered,this,&AFPSController::CallShoot);
		Input->BindAction(InputJump,ETriggerEvent::Started,this,&AFPSController::CallJump);
		Input->BindAction(InputJump,ETriggerEvent::Completed,this,&AFPSController::CallStopJump);
			
		
	}
}
void AFPSController::CallMove(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("Move Called"));
	if(PlayerPawn) PlayerPawn->Move(Value);
}

void AFPSController::CallLook(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("Look Called"));
	if(PlayerPawn) PlayerPawn->Look(Value);
}

void AFPSController::CallShoot(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("Shoot Called"));
	if(PlayerPawn) PlayerPawn->Shoot(Value);
}

void AFPSController::CallJump()
{
	UE_LOG(LogTemp,Warning,TEXT("Jump Called"));
	if(PlayerPawn) PlayerPawn->bPressedJump = true;
}

void AFPSController::CallStopJump()
{
	UE_LOG(LogTemp,Warning,TEXT("Stop Jump Called"));
	if(PlayerPawn) PlayerPawn->bPressedJump = false;
	
}



