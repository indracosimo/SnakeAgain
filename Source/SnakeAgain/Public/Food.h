// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeAgain/Public/Trigger.h"
#include "Food.generated.h"
/**
 * 
 */
UCLASS()
class SNAKEAGAIN_API AFood : public ATrigger
{
	GENERATED_BODY()
	
public:
	AFood();

	virtual void OverlappedWithSnakeHead(class ASnake* Snake);
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	

};
