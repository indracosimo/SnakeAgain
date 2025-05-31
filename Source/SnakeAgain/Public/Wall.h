// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeAgain/Public/DeadZone.h"
#include "Wall.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEAGAIN_API AWall : public ADeadZone
{
	GENERATED_BODY()
public:
	AWall();
	
	UPROPERTY(EditDefaultsOnly, Category = "Appearance")
	class UMaterialInterface* WallMaterial;

};
