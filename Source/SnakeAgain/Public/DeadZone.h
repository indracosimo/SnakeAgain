// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trigger.h"
#include "DeadZone.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEAGAIN_API ADeadZone : public ATrigger
{
	GENERATED_BODY()
public:
	void OverlappedWithSnakeHead(class ASnake* Snake);

};
