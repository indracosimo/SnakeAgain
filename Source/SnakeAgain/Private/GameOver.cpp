// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Input/Reply.h"

void UGameOver::NativeConstruct()
{
	Super::NativeConstruct();

	RestartButton->OnClicked.AddUniqueDynamic(this, &UGameOver::RestartGame);
	QuitButton->OnClicked.AddUniqueDynamic(this, &UGameOver::QuitGame);
}

void UGameOver::RestartGame()
{
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetWorld()->GetFirstPlayerController()->RestartLevel();
}

void UGameOver::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

class FReply UGameOver::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::R)
	{
		RestartGame();
		return FReply::Handled();
	}
	else if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		QuitGame();
		return FReply::Handled();
	}

	return FReply::Unhandled();
}
