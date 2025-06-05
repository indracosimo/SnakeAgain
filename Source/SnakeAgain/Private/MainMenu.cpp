// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Input/Reply.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::StartGame()
{
	//Load Level1
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, FName(TEXT("Snake1")));
	}
}

void UMainMenu::Start2PGame()
{
	//Load level1
	//with two controllable snakes, one with wasd another with arrow keys
}

void UMainMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

class FReply UMainMenu::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	return Super::NativeOnKeyDown(MyGeometry, InKeyEvent);
}
