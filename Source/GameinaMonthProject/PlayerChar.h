// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerChar.generated.h"

UCLASS()
class GAMEINAMONTHPROJECT_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();
	//Components
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "UI")
	class UCameraComponent* FPSCam;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Mesh")
	USkeletalMeshComponent* FPSArms_SK;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	UFUNCTION()
	void Shoot(const FInputActionValue& Value);
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	float Health = 100.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	float Dosh = 0.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	float WalkingSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	float SprintSpeed;

};
