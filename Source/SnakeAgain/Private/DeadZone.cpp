// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadZone.h"
#include "SnakeAgain/Public/GameModeSnake.h"
#include "SnakeAgain/Public/Snake.h"

void ADeadZone::OverlappedWithSnakeHead(class ASnake* Snake)
{
	AGameModeSnake* GameMode = Cast<AGameModeSnake>(GetWorld()->GetAuthGameMode());

	if (GameMode && !GameMode->bIsGodModeEnabled)
	{
		Snake->SetIsAlive(false);
	}
	
}
