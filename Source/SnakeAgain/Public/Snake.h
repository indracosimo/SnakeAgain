// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Snake.generated.h"

UCLASS()
class SNAKEAGAIN_API ASnake : public APawn
{
	GENERATED_BODY()

public:
	ASnake();


protected:
	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	FTimerHandle MovementTimerHandle;

	// Movement Values
	float MoveStepSize;

	FVector MoveDirection;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveUpAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveRightAction;

	UFUNCTION()
	void MoveSnake();

	void MoveUp(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);


private:
	// Snake Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* RootComp;
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* HeadMesh;

private:
	
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	TSubclassOf<class ASnakeTail> DefaultTailClass;

	TArray<class ASnakeTail*> Tails;

public:
	void SpawnTail();

private:
	class AGameModeSnake* GameMode = nullptr;
	
private:
	
	bool bIsAlive;
	bool bIsMoving;




public:
	// Conditions methods
	void SetIsAlive(bool inBIsAlive);
	


};
