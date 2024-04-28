// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerController.h"
#include "FPSController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEINAMONTHPROJECT_API AFPSController : public APlayerController
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AFPSController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//INPUT ACTIONS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InputMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InputLook;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InputJump;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InputShoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InputADS;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InputReload;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InputInteract;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InputHeal;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void CallMove(const FInputActionValue& Value);
	UFUNCTION()
	void CallLook(const FInputActionValue& Value);
	UFUNCTION()
	void CallShoot(const FInputActionValue& Value);
	UFUNCTION()
	void CallInteract(const FInputActionValue& Value);
	UFUNCTION()
	void CallADS(const FInputActionValue& Value);
	UFUNCTION()
	void CallHeal(const FInputActionValue& Value);
	UFUNCTION()
	void CallJump();
	UFUNCTION()
	void CallStopJump();
	class APlayerChar* PlayerPawn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	class AAWeapon* PrimaryWeapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	class AAWeapon* SecondaryWeapon;
protected:
	virtual void SetupInputComponent() override;
	// Called to bind functionality to input
	
};
