// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopActor.h"


#include "PlayerChar.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShopActor::AShopActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ShopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShopMesh"));
	check(ShopMesh != nullptr);
	RootComponent = ShopMesh;
	
	ShopBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Shop Box"));
	check(ShopBox != nullptr);
	ShopBox->SetupAttachment(ShopMesh);
	ShopBox->SetBoxExtent(FVector(512.f,512.f,128.f));
	ShopBox->OnComponentBeginOverlap.AddDynamic(this,&AShopActor::OnBoxBeginOverlap);
	ShopBox->OnComponentEndOverlap.AddDynamic(this,&AShopActor::OnBoxEndOverlap);
	
	bPlayerClose = false;
}

void AShopActor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("Actor Entered"));
	if(OtherActor->IsA(APlayerChar::StaticClass()))
	{
		UE_LOG(LogTemp,Warning,TEXT("Player Entered"));
		bPlayerClose = true;
		
	}
}

void AShopActor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp,Warning,TEXT("Actor left"));
	if(OtherActor->IsA(APlayerChar::StaticClass()))
	{
		UE_LOG(LogTemp,Warning,TEXT("Player left"));
		bPlayerClose = false;
	}
}

// Called when the game starts or when spawned
void AShopActor::BeginPlay()
{
	Super::BeginPlay();
	//User Interface Setup

}

// Called every frame
void AShopActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

