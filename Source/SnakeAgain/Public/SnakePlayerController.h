// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SnakePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEAGAIN_API ASnakePlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* MoveAction;

public:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

public:
	bool bIsGodModeEnabled = false;
};
