// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerChar.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "ShopActor.generated.h"

UCLASS()
class GAMEINAMONTHPROJECT_API AShopActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShopActor();
	/*Components*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* ShopMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UBoxComponent* ShopBox;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bPlayerClose;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	APlayerChar* OverlappedPlayer;
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UUserWidget* ShopUI;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> ShopUIClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
