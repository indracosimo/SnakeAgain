// Fill out your copyright notice in the Description page of Project Settings.


#include "P2_Controller.h"
#include "SnakeAgain/Public/GameModeSnake.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeAgain/Public/GameHud.h"

void AP2_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AP2_Controller::BeginPlay()
{
	Super::BeginPlay();

	GameHud = Cast<AGameHud>(GetHUD());
	if (!GameHud)
	{
		UE_LOG(LogTemp, Error, TEXT("GameHud is null"));
	}
	check(GameHud);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(P2MappingContext, 1);
	}
}

void AP2_Controller::ToggleGameOverMenu()
{
	if (GameHud)
	{
		GameHud->ShowGameOverWidget();
	}
}

void AP2_Controller::ClearScore()
{
	if (UGameplayStatics::DeleteGameInSlot(FString("SaveSlot1"), 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cleared score successfully!"))
	}
}
