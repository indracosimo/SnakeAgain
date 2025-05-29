// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeTail.generated.h"

UCLASS()
class SNAKEAGAIN_API ASnakeTail : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASnakeTail();

	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//class USceneComponent* RootComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* Mesh;
	
	virtual void BeginPlay() override;

};
