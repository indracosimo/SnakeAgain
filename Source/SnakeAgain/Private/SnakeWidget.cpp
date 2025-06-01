// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeWidget.h"
#include "Components/TextBlock.h"

USnakeWidget::USnakeWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (TXTCurrentScore)
	{
		TXTCurrentScore->SetVisibility(ESlateVisibility::Visible);
	}

	if (TXTHighScore)
	{
		TXTHighScore->SetVisibility(ESlateVisibility::Visible);
	}
	
}

void USnakeWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USnakeWidget::UpdateCurrentScore(int Value)
{
	if (TXTCurrentScore)
	{
		TXTCurrentScore->SetText(FText::FromString("Score: " + FString::FromInt(Value)));
	}
}

void USnakeWidget::UpdateHighScore(int Value)
{
	if (TXTHighScore)
	{
		TXTHighScore->SetText(FText::FromString("Hi-Score: " + FString::FromInt(Value)));
	}
}
