// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SnakeWidget.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEAGAIN_API USnakeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USnakeWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	void UpdateCurrentScore(int Value);
	void UpdateHighScore(int Value);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTCurrentScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTHighScore;
};
