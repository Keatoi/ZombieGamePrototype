// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AWeapon.h"
#include "InteractInterface.h"
#include "GameFramework/Character.h"
#include "PlayerChar.generated.h"
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractDelegate,ACharacter*,PlayerActor);
UENUM(	BlueprintType)
enum EEquippedWeapon
{
	EPrimary,
	ESecondary
};
UCLASS()
class GAMEINAMONTHPROJECT_API APlayerChar : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();
	//Components
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "UI")
	class UCameraComponent* FPSCam;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Mesh")
	USkeletalMeshComponent* FPSArms;

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
	UFUNCTION()
	void Interact(const FInputActionValue& Value);
	UFUNCTION()
	void ADS(const FInputActionValue& Value);
	UFUNCTION()
	void Heal(const FInputActionValue& Value);
	UFUNCTION()
	void HealImplementation();
	UFUNCTION()
	void HealTerminate();
	UFUNCTION(BlueprintCallable)
	void WeaponPickup( AAWeapon* Pickup);
	UPROPERTY()
	FInteractDelegate OnInteract;
	UPROPERTY()
	FTimerHandle HealHandle;
	UPROPERTY()
	FTimerHandle TerminateHandle;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	float Health = 100.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	float HealAmount = 10.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	float Armour = 100.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	float Dosh = 0.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	float WalkingSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	float SprintSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	bool bInvertControls;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	float HPS = 3.f;//Health to heal per second
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	int MedKits = 1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	bool bisADS = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	TArray<AAWeapon*> EquippedWeapons;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Values")
	AAWeapon* PrimaryWeapon;
	

};
