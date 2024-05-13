// Fill out your copyright notice in the Description page of Project Settings.


#include "AWeapon.h"
#include "Particles/ParticleSystemComponent.h"

#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAWeapon::AAWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GunSK = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SightSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sight"));
	SightSM->SetupAttachment(GunSK,FName("SightSocket"));
}

// Called when the game starts or when spawned
void AAWeapon::BeginPlay()
{
	Super::BeginPlay();
	GameModeRef = Cast<AFPSGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	//AmmoDisplay = AmmoReserve - MagazineAmmoMax;
}



void AAWeapon::ReloadStart()
{
	//UE_LOG(LogTemp, Log, TEXT("ReloadStart"));
	if(MagazineAmmo != MagazineAmmoMax)
	{
		bCanFire = false;
		if(SB_Reload) UGameplayStatics::PlaySoundAtLocation(this,SB_Reload,GetActorLocation());
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &AAWeapon::ReloadEnd, ReloadTime, false); 
	}
	
}

void AAWeapon::Fire()
{
	if(MagazineAmmo > 0 && bCanFire && !bIsAuto)
	{
		if(SB_Fire)UGameplayStatics::PlaySoundAtLocation(this,SB_Fire,GetActorLocation());
		FHitResult Hit;
		FVector TraceStart = GunSK->GetSocketLocation(FName("Muzzle"));
		FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * Range;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		GetWorld()->LineTraceSingleByChannel(Hit,TraceStart,TraceEnd,TraceChannelProperty,QueryParams);
		
		if (MuzzleSystem)
		{
			FVector Scale = {0.1f,0.1f,0.1f};
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),MuzzleSystem,TraceStart,FRotator::ZeroRotator,Scale);
		}
		if(bDebug)
		{
			DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
			UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());
		}
		if (Hit.bBlockingHit && IsValid(Hit.GetActor())&& Hit.GetActor()->ActorHasTag("AI"))
		{
			if(bDebug) UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
			

			if(Hit.BoneName == FName("Head") || Hit.BoneName == FName("Spine2"))
			{
				if(bDebug) UE_LOG(LogTemp, Log, TEXT("Trace hit Bone: %s"), *Hit.BoneName.ToString());
				FDamageEvent DamageEvent;
				Hit.GetActor()->TakeDamage((BaseDamage * 3.f),DamageEvent,UGameplayStatics::GetPlayerController(GetWorld(),0),this);
				if(GameModeRef) GameModeRef->AddScore(100.f);
			}
			else
			{
				if(bDebug) UE_LOG(LogTemp, Log, TEXT("Trace hit : %s"), *Hit.GetActor()->GetName());
				FDamageEvent DamageEvent;
				Hit.GetActor()->TakeDamage(BaseDamage,DamageEvent,UGameplayStatics::GetPlayerController(GetWorld(),0),this);
				if(GameModeRef) GameModeRef->AddScore(50.f);
			}
		}
		else if (bDebug)
		{
			UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
		}
		MagazineAmmo --;
	}
	else if(MagazineAmmo > 0 && bCanFire && bIsAuto)
	{
		GetWorld()->GetTimerManager().SetTimer(AutoTimer,this,&AAWeapon::AutoFire,FireRate,true,0.001f);
	}
	else if(SB_Empty)UGameplayStatics::PlaySoundAtLocation(this,SB_Empty,GetActorLocation());
}

void AAWeapon::FireEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(AutoTimer);
}

void AAWeapon::ReloadEnd()
{
	//Subtract MagazineAmountMax from Reserve
	if(MagazineAmmo != MagazineAmmoMax)
	{
		AmmoReserve -= MagazineAmmoMax;
		AmmoDisplay = AmmoReserve - MagazineAmmoMax;
		if(AmmoDisplay < 0) AmmoDisplay = 0;
		//If MagMax is less than ammo reserve set it to be the value of magazine else set the remainder of ammo reserve to fill the magazine
		if(AmmoReserve >= MagazineAmmoMax) MagazineAmmo = MagazineAmmoMax;
		else MagazineAmmo = AmmoReserve;
		if(AmmoReserve < 0 )AmmoReserve = 0;
		if(bDebug) UE_LOG(LogTemp, Log, TEXT("MagAmmo: %d"), MagazineAmmo);UE_LOG(LogTemp, Log, TEXT("Reserve Ammo: %d"),AmmoReserve)
		bCanFire = true;
	}
	
}

void AAWeapon::AutoFire()
{
	if(MagazineAmmo > 0 && bCanFire)
	{
		if(SB_Fire)UGameplayStatics::PlaySoundAtLocation(this,SB_Fire,GetActorLocation());
		FHitResult Hit;
		FVector TraceStart = GunSK->GetSocketLocation(FName("Muzzle"));
		FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * Range;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		GetWorld()->LineTraceSingleByChannel(Hit,TraceStart,TraceEnd,TraceChannelProperty,QueryParams);
		if (MuzzleSystem)
		{
			FVector Scale = {0.1f,0.1f,0.1f};
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),MuzzleSystem,TraceStart,FRotator::ZeroRotator,Scale);
		}
		
		if(bDebug)
		{
			DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
			UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());
		}
		if (Hit.bBlockingHit && IsValid(Hit.GetActor())&& Hit.GetActor()->ActorHasTag("AI"))
		{
			if(bDebug) UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
			

			if(Hit.BoneName == FName("Head") || Hit.BoneName == FName("Spine2"))
			{
				if(bDebug) UE_LOG(LogTemp, Log, TEXT("Trace hit Bone: %s"), *Hit.BoneName.ToString());
				FDamageEvent DamageEvent;
				Hit.GetActor()->TakeDamage(150.f,DamageEvent,UGameplayStatics::GetPlayerController(GetWorld(),0),this);
				if(GameModeRef) GameModeRef->AddScore(100.f);
			}
			else
			{
				if(bDebug) UE_LOG(LogTemp, Log, TEXT("Trace hit Bone: %s"), *Hit.BoneName.ToString());
				FDamageEvent DamageEvent;
				Hit.GetActor()->TakeDamage(50.f,DamageEvent,UGameplayStatics::GetPlayerController(GetWorld(),0),this);
				if(GameModeRef) GameModeRef->AddScore(50.f);
			}
		}
		else if (bDebug)
		{
			UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
		}
		MagazineAmmo --;
	}
	else if(SB_Empty)UGameplayStatics::PlaySoundAtLocation(this,SB_Empty,GetActorLocation());
}

// Called every frame
void AAWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RemainingTime = GetWorld()->GetTimerManager().GetTimerElapsed(ReloadTimer);
}

