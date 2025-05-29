// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigger.generated.h"

UCLASS()
class SNAKEAGAIN_API ATrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	// Called every frame
//	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
//	class USceneComponent* RootComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* Mesh;


	
public:
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	virtual void OverlapedWithSnakeHead(class ASnake* Snake) PURE_VIRTUAL(ATrigerable::OverlapedWithSnakeHead);
};
