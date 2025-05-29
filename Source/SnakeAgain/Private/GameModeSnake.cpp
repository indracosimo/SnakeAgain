// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeAgain/Public/GameModeSnake.h"
#include "SnakeAgain/Public/Snake.h"
#include "SnakeAgain/Public/Food.h"
#include "SnakeAgain/Public/Arena.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "SnakeAgain/Public/SnakePlayerController.h"

AGameModeSnake::AGameModeSnake()
{
	DefaultPawnClass = ASnake::StaticClass();
	//HUDClass = ASnakeHud::StaticClass();
	PlayerControllerClass = ASnakePlayerController::StaticClass();

//	bViewDebugLines = false;

	ArenaHeight = 1500;
	ArenaWidth = 1700;

	SquareWidth = 100.f;

	ArenaSpawnCenter = FVector(50, -50, 0);

	// Camera Location
	CameraHeight = ArenaHeight * 1.2;
	CameraSpawnLocation = FVector(50.0, -50.0, CameraHeight);
	CameraSpawnRotation = FRotator(-90.0, 0.0, 0.0);
}

void AGameModeSnake::StartPlay()
{
	Super::StartPlay();
	
	SpawnCamera();
	SpawnArena();
	
}

void AGameModeSnake::SpawnCamera()
{
	ACameraActor* PlayerViewCamera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), CameraSpawnLocation, CameraSpawnRotation, FActorSpawnParameters());
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

	if (PC)
	{
		PlayerViewCamera->SetOwner(PC);
		PC->SetViewTarget(PlayerViewCamera);
	}
}

void AGameModeSnake::SpawnArena()
{
	FTransform SpawnTransform = FTransform(FRotator(), ArenaSpawnCenter, FVector(ArenaHeight, ArenaWidth, 1));
	Arena = GetWorld()->SpawnActor<AArena>(ArenaClass, SpawnTransform, FActorSpawnParameters());

	// For debugging the grid
	//ViewDebugLines();
}

void AGameModeSnake::OnSnakeOverlapFood()
{
	ASnake* Snake = Cast<ASnake>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Snake)
	{
		Snake->SpawnTail();
		SpawnFood();
	}
}

void AGameModeSnake::SpawnFood()
{
	const float GridHighet = 0.0f;

	FVector TopLeft = GetBottomPoint();
	
	float SpawnX = FMath::RandRange(0, ArenaHeight /100 - 1);
	float SpawnY = FMath::RandRange(0, ArenaWidth /100 - 1);
	float SpawnYaw = FMath::FRandRange(0.f, 360.f);
	
	FVector UpperLeft = TopLeft + FVector(SpawnX * SquareWidth, SpawnY * SquareWidth, GridHighet);
	FVector LowerRight = TopLeft + FVector(SpawnX * SquareWidth + SquareWidth, SpawnY * SquareWidth + SquareWidth, GridHighet);
	
	FVector SpawnLocation = FVector(((UpperLeft.X + LowerRight.X) / 2.0f), ((UpperLeft.Y + LowerRight.Y) / 2.0f), 5.0f);
	FRotator SpawnRotation = FRotator(0.0f, SpawnYaw, 0.0f);

	GetWorld()->SpawnActor<AFood>(FoodClass, SpawnLocation, SpawnRotation, FActorSpawnParameters());
}

FVector AGameModeSnake::GetBottomPoint() const
{
	return FVector(-(ArenaHeight / 2), -(ArenaWidth / 2), 1) + ArenaSpawnCenter;
}

