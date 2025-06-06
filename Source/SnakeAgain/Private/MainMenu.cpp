// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "GameHud.h"
#include "UGameDataSubsystem.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Input/Reply.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::StartGame);
	Start2PButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::Start2PGame);
	QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::QuitGame);
}

void UMainMenu::StartGame()
{
	//Load Level1
//UWorld* World = GetWorld();
//if (World)
//{
//	UGameplayStatics::OpenLevel(World, FName(TEXT("Snake1")));
//}
	
	if (GetWorld() && GetWorld()->GetFirstPlayerController())
	{
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
	}
	
	RemoveFromParent();
	
	if (AGameHud* GameHUD = Cast<AGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		GameHUD->CreateSnakeWidget();
	}

//	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
//
//	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
//	GetWorld()->GetFirstPlayerController()->RestartLevel();
}

void UMainMenu::Start2PGame()
{
	//Load level1
//	StartGame();

	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if (UUGameDataSubsystem* GameDataSubsysten = GameInstance->GetSubsystem<UUGameDataSubsystem>())
		{
			GameDataSubsysten->SetTwoPlayer(true);
			GameDataSubsysten->SetVsAi(false);
		}
	}

	StartGame();
	//with two controllable snakes, one with wasd another with arrow keys
}

void UMainMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

class FReply UMainMenu::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	//return Super::NativeOnKeyDown(MyGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == EKeys::S)
	{
		StartGame();
		return FReply::Handled();
	}
	else if (InKeyEvent.GetKey() == EKeys::Tab)
	{
		QuitGame();
		return FReply::Handled();
	}

	return FReply::Unhandled();
}
