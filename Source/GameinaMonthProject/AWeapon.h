// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSGameModeBase.h"
#include "GameFramework/Actor.h"
#include "AWeapon.generated.h"
UENUM(	BlueprintType)
enum EEquippedWeapon
{
	EPrimary,
	ESecondary
};
UCLASS()
class GAMEINAMONTHPROJECT_API AAWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAWeapon();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USkeletalMeshComponent* GunSK;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* SightSM;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Sounds")
	USoundBase* SB_Fire;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Sounds")
	USoundBase* SB_Empty;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Sounds")
	USoundBase* SB_Reload;
	UFUNCTION()
	void ReloadStart();
	UFUNCTION()
	void Fire();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void ReloadEnd();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UUserWidget* InteractUI;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Varaibles")
	AFPSGameModeBase* GameModeRef;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> InteractUIClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Varaibles")
	float BaseDamage = 50.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Varaibles")
	FName WeaponName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Varaibles")
	float Price;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Varaibles")
	float Range = 1250.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Varaibles")
	float ReloadTime = 3.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Varaibles")
	float RemainingTime;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Varaibles")
	int MagazineAmmo = 30;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Varaibles")
	int MagazineAmmoMax = 30;//Max amount of ammo the gun can have in a mag
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Varaibles")
	int AmmoReserve = 90;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Varaibles")
	bool bIsAuto = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Varaibles")
	bool bCanFire = true;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Varaibles")
	bool bDebug = true;
	UPROPERTY(EditAnywhere, Category="Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon Varaibles")
	FTimerHandle ReloadTimer;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TEnumAsByte<EEquippedWeapon> WeaponType;

};
