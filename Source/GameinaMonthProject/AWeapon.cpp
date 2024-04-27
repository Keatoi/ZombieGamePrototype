// Fill out your copyright notice in the Description page of Project Settings.


#include "AWeapon.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AAWeapon::AAWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GunSK = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AAWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAWeapon::ReloadStart()
{
	if(MagazineAmmo != MagazineAmmoMax)
	{
		if(SB_Reload) UGameplayStatics::PlaySoundAtLocation(this,SB_Reload,GetActorLocation());
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &AAWeapon::ReloadEnd, ReloadTime, false); 
	}
	
}

void AAWeapon::Fire()
{
	if(MagazineAmmo > 0)
	{
		if(SB_Fire)UGameplayStatics::PlaySoundAtLocation(this,SB_Fire,GetActorLocation());
		FHitResult Hit;
		FVector TraceStart = GetActorLocation();
		FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * Range;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		GetWorld()->LineTraceSingleByChannel(Hit,TraceStart,TraceEnd,TraceChannelProperty,QueryParams);
		if(bDebug)
		{
			DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
			UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());
		}
		if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
		{
			if(bDebug) UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
			
		}
		else if (bDebug)
		{
			UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
		}
	}
	else if(SB_Empty)UGameplayStatics::PlaySoundAtLocation(this,SB_Empty,GetActorLocation());
}

void AAWeapon::ReloadEnd()
{
	//Subtract MagazineAmountMax from Reserve
	if(MagazineAmmo != MagazineAmmoMax)
	{
		AmmoReserve -= MagazineAmmoMax;
		//If MagMax is less than ammo reserve set it to be the value of magazine else set the remainder of ammo reserve to fill the magazine
		if(AmmoReserve >= MagazineAmmoMax) MagazineAmmo = MagazineAmmoMax;
		else MagazineAmmo = AmmoReserve;
		if(AmmoReserve < 0 )AmmoReserve = 0;
	}
	
}

// Called every frame
void AAWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

