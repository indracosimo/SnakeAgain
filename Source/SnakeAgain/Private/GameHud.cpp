// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHud.h"
#include "SnakeAgain/Public/GameOver.h"
#include "SnakeAgain/Public/SnakeWidget.h"
#include "SnakeAgain/Public/GameModeSnake.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void AGameHud::DrawHUD()
{
	Super::DrawHUD();
}

void AGameHud::BeginPlay()
{
	Super::BeginPlay();

	CreateSnakeWidget();
}

void AGameHud::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGameHud::CreateSnakeWidget()
{
	if (SnakeWidgetClass)
	{
		SnakeWidget = CreateWidget<USnakeWidget>(GetWorld(), SnakeWidgetClass);

		if (SnakeWidget)
		{
			SnakeWidget->AddToViewport();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("SnakeWidget could not be created"));
		}
	}
}

//void AGameHud::CreatePauseMenuWidget()
//{
//	
//}

void AGameHud::UpdateCurrentScore(int Value)
{
	if (SnakeWidget)
	{
		SnakeWidget->UpdateCurrentScore(Value);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SnakeWidget is null"));
	}
}

void AGameHud::UpdateHighScore(int Value)
{
	if (SnakeWidget)
	{
		SnakeWidget->UpdateHighScore(Value);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SnakeWidget is null"));
	}
}

void AGameHud::ShowGameOverWidget()
{
	if (GameOverWidgetClass)
	{
		GameOverWidget = CreateWidget<UGameOver>(GetWorld(), GameOverWidgetClass);

		if (GameOverWidget)
		{
			GameOverWidget->AddToViewport();
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
			GameOverWidget->SetIsFocusable(true);
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), GameOverWidget);
		}
	}
}
