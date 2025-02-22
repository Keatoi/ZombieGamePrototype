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
	bShopOpen = false;
	
}

void AShopActor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("Actor Entered"));
	if(OtherActor->IsA(APlayerChar::StaticClass()))
	{
		UE_LOG(LogTemp,Warning,TEXT("Player Entered"));
		bPlayerClose = true;
		OverlappedPlayer = Cast<APlayerChar>(OtherActor);
		if(InteractUI) InteractUI->AddToViewport();
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
		OverlappedPlayer = nullptr;
		if(OverlappedPlayer == nullptr)
		{
			UE_LOG(LogTemp,Warning,TEXT("Player null"));
			if(InteractUI) InteractUI->RemoveFromParent();
			UE_LOG(LogTemp,Warning,TEXT("ClosingShop"));
			ShopUI->RemoveFromParent();
			if(PC)
			{
				PC->SetInputMode(FInputModeGameOnly());
				PC->SetShowMouseCursor(false);
			}
			bShopOpen = false;
		}
	}
}

void AShopActor::OnInteract(ACharacter* PlayerActor)
{
	if(OverlappedPlayer != nullptr)
	{
		
		if(ShopUI && !bShopOpen)
		{
			UE_LOG(LogTemp,Warning,TEXT("OpeningShop"));
			InteractUI->RemoveFromParent();
			ShopUI->AddToViewport(1);
			if(PC)
			{
				PC->SetInputMode(FInputModeGameAndUI());
				PC->SetShowMouseCursor(true);
			}
			bShopOpen = true;
		}
		else if(ShopUI && bShopOpen)
		{
			UE_LOG(LogTemp,Warning,TEXT("ClosingShop"));
			ShopUI->RemoveFromParent();
			InteractUI->AddToViewport();
			if(PC)
			{
				PC->SetInputMode(FInputModeGameOnly());
				PC->SetShowMouseCursor(false);
			}
			bShopOpen = false;
		}
	}
}

// Called when the game starts or when spawned
void AShopActor::BeginPlay()
{
	Super::BeginPlay();
	if(InteractUIClass)
	{
		UE_LOG(LogTemp,Warning,TEXT("Interact UI class loaded"));
		InteractUI = CreateWidget(GetWorld(),InteractUIClass);
	}
	if(ShopUIClass)
	{
		UE_LOG(LogTemp,Warning,TEXT("Shop UI class loaded"));
		ShopUI = CreateWidget(GetWorld(),ShopUIClass);
	}
	ACharacter* FoundPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	PlayerRef = Cast<APlayerChar>(FoundPlayer);
	if(PlayerRef)
	{
		PlayerRef->OnInteract.AddDynamic(this,&AShopActor::OnInteract);
	}
	PC = Cast<AFPSController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if(PC)
	{
		UE_LOG(LogTemp,Warning,TEXT("Shop PC loaded"));
	}
	//User Interface Setup

}

// Called every frame
void AShopActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

