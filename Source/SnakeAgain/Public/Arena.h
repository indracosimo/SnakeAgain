// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Arena.generated.h"

UCLASS()
class SNAKEAGAIN_API AArena : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AArena();
	void BeginPlay() override;
	void GetRandomFoodSpawnLocation(FVector& OutLocation);

private:
	void SpawnWall(FVector SpawnLocation, FVector SpawnScale);

private:
	float WallWidth;
	float WallHeight;

public:

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class UMaterialInterface* ArenaGameOverMaterial;
};
