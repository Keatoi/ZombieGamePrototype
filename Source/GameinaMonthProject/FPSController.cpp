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
		Input->BindAction(InputShoot,ETriggerEvent::Started,this,&AFPSController::CallShoot);
		Input->BindAction(InputShoot,ETriggerEvent::Completed,this,&AFPSController::CallStopShooting);
		Input->BindAction(InputJump,ETriggerEvent::Started,this,&AFPSController::CallJump);
		Input->BindAction(InputJump,ETriggerEvent::Completed,this,&AFPSController::CallStopJump);
		Input->BindAction(InputInteract,ETriggerEvent::Started,this,&AFPSController::CallInteract);
		Input->BindAction(InputADS,ETriggerEvent::Started,this,&AFPSController::CallADS);
		Input->BindAction(InputHeal,ETriggerEvent::Started,this,&AFPSController::CallHeal);
		Input->BindAction(InputReload,ETriggerEvent::Started,this,&AFPSController::CallReload);
			
		
	}
}
void AFPSController::CallMove(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp,Warning,TEXT("Move Called"));
	if(PlayerPawn->Health > 0.f) PlayerPawn->Move(Value);
}

void AFPSController::CallLook(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp,Warning,TEXT("Look Called"));
	if(PlayerPawn->Health > 0.f) PlayerPawn->Look(Value);
}

void AFPSController::CallShoot(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp,Warning,TEXT("Shoot Called"));
	if(PlayerPawn->Health > 0.f) PlayerPawn->Shoot(Value);
}

void AFPSController::CallInteract(const FInputActionValue& Value)
{
	if(PlayerPawn->Health > 0.f) PlayerPawn->Interact(Value);
}

void AFPSController::CallADS(const FInputActionValue& Value)
{
	if(PlayerPawn->Health > 0.f) PlayerPawn->ADS(Value);
}

void AFPSController::CallHeal(const FInputActionValue& Value)
{
	if(PlayerPawn->Health > 0.f) PlayerPawn->Heal(Value);
}

void AFPSController::CallJump()
{
	//UE_LOG(LogTemp,Warning,TEXT("Jump Called"));
	if(PlayerPawn->Health > 0.f) PlayerPawn->bPressedJump = true;
}

void AFPSController::CallStopJump()
{
	//UE_LOG(LogTemp,Warning,TEXT("Stop Jump Called"));
	if(PlayerPawn) PlayerPawn->bPressedJump = false;
	
}

void AFPSController::CallReload()
{
	UE_LOG(LogTemp, Log, TEXT("Call Reload"));
	if(PlayerPawn->Health > 0.f && PlayerPawn->CurrentWeapon)
	{
		PlayerPawn->CurrentWeapon->ReloadStart();
	}
}

void AFPSController::CallStopShooting()
{
	if(PlayerPawn->Health > 0.f && PlayerPawn->CurrentWeapon)
	{
		PlayerPawn->CurrentWeapon->ReloadEnd();
	}
}



