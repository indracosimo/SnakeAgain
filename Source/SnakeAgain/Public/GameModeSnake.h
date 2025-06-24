// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeSnake.generated.h"

class AFood;

/**
 * 
 */
UCLASS()
class SNAKEAGAIN_API AGameModeSnake : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameModeSnake();

	bool bIsGodModeEnabled = false;
	int32 PlayerIndex;
	class AArena* Arena;

	UPROPERTY(EditDefaultsOnly, Category = "Arena settings")
	int32 ArenaWidth;
	UPROPERTY(EditDefaultsOnly, Category = "Arena settings")
	int32 ArenaHeight;
	UPROPERTY(EditDefaultsOnly, Category = "Arena settings")
	float SquareWidth;
	UPROPERTY(EditDefaultsOnly, Category = "Arena settings")
	float CameraHeight;
	UPROPERTY(EditDefaultsOnly, Category = "Arena settings")
	FVector ArenaSpawnCenter;
	UPROPERTY(EditDefaultsOnly, Category = "Arena settings")
	FVector CameraSpawnLocation;
	UPROPERTY(EditDefaultsOnly, Category = "Arena settings")
	FRotator CameraSpawnRotation;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn settings")
	FVector PlayerSpawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn settings")
	int32 FoodSpawnRangeX;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn settings")
	int32 FoodSpawnRangeY;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn settings")
	int32 FoodSpawnRangeZ;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Arena")
	TSubclassOf<class AArena> ArenaClass;

	UPROPERTY(EditDefaultsOnly, Category = "Food")
	TSubclassOf<class AFood> FoodClass;

private:
	int Score;

	int HighScore;
	
protected:
	virtual void StartPlay() override;

private:
	void SpawnCamera();
	
	void SpawnArena();

	void CreateGrid();

	void PlacePointOnGrid();

	void UpdateHUD();

	void IncreaseScore();
	//void ViewDebugLines();

public:
	void OnSnakeOverlapFood();
	void SpawnSnake(int32 PlayerIndex);
	void SpawnFood();

	void GameOver();
	
	FVector GetBottomPoint() const;
};