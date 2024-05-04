// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameModeBase.h"

#include "FPSController.h"

AFPSGameModeBase::AFPSGameModeBase()
{
	PlayerControllerClass = AFPSController::StaticClass();
}

void AFPSGameModeBase::AddScore(int ScoreToAdd)
{
	Score += ScoreToAdd;
	Cash += ScoreToAdd;
}

void AFPSGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
