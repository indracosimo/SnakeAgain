// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UGameDataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEAGAIN_API UUGameDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameData")
	bool bTwoPlayer = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameData")
	bool bVsAI = false;

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void SetTwoPlayer(bool bNewTwoPlayer);

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void SetVsAi(bool bNewVsAI);
};
