// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "P2_Controller.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEAGAIN_API AP2_Controller : public APlayerController
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputMappingContext* P2MappingContext;
	
public:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	void ToggleGameOverMenu();

	void ClearScore();

private:
	class AGameHud* GameHud = nullptr;

public:
	bool bIsGodModeEnabled = false;
};
