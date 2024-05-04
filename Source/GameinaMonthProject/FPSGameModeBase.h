// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEINAMONTHPROJECT_API AFPSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	AFPSGameModeBase();
public:
	UFUNCTION(BlueprintCallable)
	void AddScore(int ScoreToAdd);
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Score;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Cash;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
