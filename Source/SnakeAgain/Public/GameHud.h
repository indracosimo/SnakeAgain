// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHud.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEAGAIN_API AGameHud : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;
		
	void CreateSnakeWidget();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UUserWidget> SnakeWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UUserWidget> GameOverWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UUserWidget> MainMenuWidgetClass;

private:

	class USnakeWidget* SnakeWidget = nullptr;

	class UGameOver* GameOverWidget = nullptr;

	class UMainMenu* MainMenuWidget = nullptr;

private:
	
//	void CreateSnakeWidget();

	//void CreatePauseMenuWidget();

public:
	
	UFUNCTION()
	void UpdateCurrentScore(int Value);
	
	UFUNCTION()
	void UpdateHighScore(int Value);

	UFUNCTION()
	void ShowGameOverWidget();

	UFUNCTION()
	void ShowMainMenuWidget();
};
