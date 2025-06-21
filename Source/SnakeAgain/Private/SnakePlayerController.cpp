// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeAgain/Public/SnakePlayerController.h"
#include "SnakeAgain/Public/GameModeSnake.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeAgain/Public/GameHud.h"

void ASnakePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ASnakePlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameHud = Cast<AGameHud>(GetHUD());
	if (!GameHud)
	{
		UE_LOG(LogTemp, Error, TEXT("GameHud is null"));
	}
	check(GameHud);
}

void ASnakePlayerController::ToggleGameOverMenu()
{
	if (GameHud)
	{
		GameHud->ShowGameOverWidget();
	}
}

void ASnakePlayerController::ClearScore()
{
	if (UGameplayStatics::DeleteGameInSlot(FString("SaveSlot1"), 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cleared score successfully!"))
	}
}

