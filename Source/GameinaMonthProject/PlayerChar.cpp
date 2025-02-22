// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"

#include "InputActionValue.h"
#include "ShopActor.h"
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
	FPSCam->SetRelativeLocation(FVector(0.f,0.f,0.f));
	FPSCam->SetupAttachment(GetCapsuleComponent());
	//Create FPS Arms mesh and set to only be seen by its player
	FPSArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPS ARMS"));
	check(FPSArms != nullptr);
	FPSArms->SetOnlyOwnerSee(true);
	FPSArms->SetupAttachment(FPSCam);
	//Disable Shadows
	FPSArms->bCastDynamicShadow = false;
	FPSArms->CastShadow = false;
	FVector ArmPos = {-20.f,-15.f,-150.5f};
	FPSArms->SetRelativeLocation(ArmPos);
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
		//UE_LOG(LogTemp,Warning,TEXT("Move Value Y %f"),Value.Get<FVector2D>().Y);`
		// Get forward vector
		const FVector Direction = GetActorForwardVector();
		UE_LOG(LogTemp,Warning,TEXT("Direction %s"),*Direction.ToString());
		AddMovementInput(Direction, MoveValue.Y);
	}
 
	// Right/Left direction
	if (MoveValue.X != 0.f)
	{
		UE_LOG(LogTemp,Warning,TEXT("Move Value %f"),Value.Get<FVector2D>().X);
		// Get right vector
		const FVector Direction = GetActorRightVector();
		UE_LOG(LogTemp,Warning,TEXT("Direction %s"),*Direction.ToString());
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
	if(CurrentWeapon)
	{
		CurrentWeapon->bDebug = true;
		CurrentWeapon->Fire();
		
		if(CurrentWeapon->bCanFire)
		{
			if(FireMontage)
			{
				PlayAnimMontage(FireMontage,1);
			}
			float YawRecoil = FMath::RandRange(-0.2,0.1);
			float PitchRecoil = FMath::RandRange(-0.2,0.1);
			AddControllerYawInput(YawRecoil);
			AddControllerPitchInput(PitchRecoil);
		
		}
		
	}
}

void APlayerChar::Interact(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("Interact"));
	OnInteract.Broadcast(this);
}

void APlayerChar::ADS(const FInputActionValue& Value)
{

	if(bisADS)
	{
		UE_LOG(LogTemp,Warning,TEXT("not ADS"));
		FVector ArmPos = {-20.f,-15.f,-150.5f};
		FRotator ArmRot = {0.f,0.f,0.f};
		FPSArms->SetRelativeRotation(ArmRot);
		FPSArms->SetRelativeLocation(ArmPos);
		bisADS = false;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("ADS"));
		bisADS = true;
		FVector ArmPos = {-20.f,-15.f,-136.79f};
		FRotator ArmRot = {0.f,0.f,0.f};
		FPSArms->SetRelativeRotation(ArmRot);
		FPSArms->SetRelativeLocation(ArmPos);
		
	}
}

void APlayerChar::Heal(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("Heal"));
	if(MedKits > 0 && Health < 100.f)
	{
		MedKits --;
		GetWorld()->GetTimerManager().SetTimer(TerminateHandle,this,&APlayerChar::HealTerminate,6.f,false);
		GetWorld()->GetTimerManager().SetTimer(HealHandle,this, &APlayerChar::HealImplementation,1.f,true);
	}
}

void APlayerChar::HealImplementation()
{
	UE_LOG(LogTemp,Warning,TEXT("HealImp"));
	if(Health <= 100.f)
	{
		float TempHealth = Health;
		TempHealth += HealAmount;
		
		Health = FMath::Clamp(TempHealth,0.f,100.f);
	}
}

void APlayerChar::HealTerminate()
{
	GetWorld()->GetTimerManager().ClearTimer(HealHandle);
	GetWorld()->GetTimerManager().ClearTimer(TerminateHandle);
}

void APlayerChar::WeaponPickup(AAWeapon* Pickup)
{
	AAWeapon* NewWeap = Cast<AAWeapon>(Pickup);
	if(NewWeap)
	{
		if(NewWeap->WeaponType == EPrimary && CurrentWeapon != PrimaryWeapon)
		{
			if(PrimaryWeapon)
			{
				PrimaryWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				PrimaryWeapon->Destroy();
				PrimaryWeapon = nullptr;
			}
			if(CurrentWeapon == BackupWeapon)
			{
				BackupWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				BackupWeapon->AttachToComponent(FPSArms,FAttachmentTransformRules::KeepWorldTransform,FName("BackupPoint"));
			}
			PrimaryWeapon = NewWeap;
			CurrentWeapon = PrimaryWeapon;
			CurrentWeapon->AttachToComponent(FPSArms,FAttachmentTransformRules::KeepWorldTransform,FName("GripPoint"));
		}
		else if(NewWeap->WeaponType == ESecondary && CurrentWeapon != BackupWeapon)
		{
			if(BackupWeapon)
			{
				BackupWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				BackupWeapon->Destroy();
				BackupWeapon = nullptr;
			}
			if(CurrentWeapon == PrimaryWeapon)
			{
				PrimaryWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				PrimaryWeapon->AttachToComponent(FPSArms,FAttachmentTransformRules::KeepWorldTransform,FName("BackupPoint"));
			}
			BackupWeapon = NewWeap;
			CurrentWeapon = BackupWeapon;
			CurrentWeapon->AttachToComponent(FPSArms,FAttachmentTransformRules::KeepWorldTransform,FName("GripPoint"));
		}
	}
}



