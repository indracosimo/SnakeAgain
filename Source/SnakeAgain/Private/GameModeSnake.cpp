// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeAgain/Public/GameModeSnake.h"

#include "UGameDataSubsystem.h"
#include "SnakeAgain/Public/Snake.h"
#include "SnakeAgain/Public/Food.h"
#include "SnakeAgain/Public/Arena.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "SnakeAgain/Public/GameHud.h"
#include "Camera/CameraActor.h"
#include "SnakeAgain/Public/SnakePlayerController.h"

AGameModeSnake::AGameModeSnake()
{
	DefaultPawnClass = nullptr; //ASnake::StaticClass();
	HUDClass = AGameHud::StaticClass();
	PlayerControllerClass = ASnakePlayerController::StaticClass();

//	bViewDebugLines = false;

	ArenaHeight = 2000;
	ArenaWidth = 2000;

	SquareWidth = 100.f;

	ArenaSpawnCenter = FVector(50, -50, 250);

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
	SpawnFood();

	if (UUGameDataSubsystem* GameSubSys = GetGameInstance()->GetSubsystem<UUGameDataSubsystem>())
	{
		SpawnSnake(0);

		if (GameSubSys->IsTwoPlayer())
		{
			SpawnSnake(1);
		}
	}
}
void AGameModeSnake::SpawnSnake(int32 InPlayerIndex )
{
	FVector SpawnOffset = FVector(0, InPlayerIndex == 0 ? -200 : 200, 250);
	FVector SpawnLocation = ArenaSpawnCenter + SpawnOffset;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ASnake* NewSnake = GetWorld()->SpawnActor<ASnake>(ASnake::StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnParams);

	APlayerController* PC = UGameplayStatics::CreatePlayer(GetWorld(), PlayerIndex, true);
	if (PC && NewSnake)
	{
		PC->Possess(NewSnake);
	}
}
void AGameModeSnake::BeginPlay()
{
	Super::BeginPlay();

	//UUGameDataSubsystem*
	
//	GameSubSys = GetWorld()->GetSubsystem<UUGameDataSubsystem>();
	if (MainMenuWidgetClass)
	{
		UUserWidget* MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			
			if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
			{
				FInputModeUIOnly InputMode;
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				InputMode.SetWidgetToFocus(MenuWidget->TakeWidget());
				PlayerController->SetInputMode(InputMode);
			}
		}
	}

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



FVector AGameModeSnake::GetBottomPoint() const
{
	return FVector(-(ArenaHeight / 2), -(ArenaWidth / 2), 1) + ArenaSpawnCenter;
}

void AGameModeSnake::SpawnFood()
{
	const float GridHeight = ArenaSpawnCenter.Z;

	FVector TopLeft = GetBottomPoint();

	float SpawnX = FMath::RandRange(0, ArenaHeight /100 - 1);
	float SpawnY = FMath::RandRange(0, ArenaWidth /100 - 1);
	float SpawnYaw = FMath::FRandRange(0.f, 360.f);
	
	FVector UpperLeft = TopLeft + FVector(SpawnX * SquareWidth, SpawnY * SquareWidth, GridHeight);
	FVector LowerRight = TopLeft + FVector(SpawnX * SquareWidth + SquareWidth, SpawnY * SquareWidth + SquareWidth, GridHeight);
	
	FVector SpawnLocation = FVector(((UpperLeft.X + LowerRight.X) / 2.0f), ((UpperLeft.Y + LowerRight.Y) / 2.0f), GridHeight);
	FRotator SpawnRotation = FRotator(0.0f, SpawnYaw, 0.0f);

	GetWorld()->SpawnActor<AFood>(FoodClass, SpawnLocation, SpawnRotation, FActorSpawnParameters());
}

void AGameModeSnake::GameOver()
{
	Arena->GetStaticMeshComponent()->SetVisibility(false);
	ASnakePlayerController* SnakePlayerController = Cast<ASnakePlayerController>(GetWorld()->GetFirstPlayerController());

	if (SnakePlayerController) 
	{
		SnakePlayerController->ToggleGameOverMenu();
	}
}

void AGameModeSnake::CreateGrid()
{
	FVector TopLeft = GetBottomPoint();
	float GridHeight = 1.f;

	for (int32 i = 0; i < ArenaHeight /100 + 1; i++)
	{
		FVector Start = TopLeft + FVector(i * SquareWidth, 0.f, GridHeight);
		FVector End = Start + FVector(0.f, ArenaWidth, GridHeight);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);
	}

	for (int32 i = 0; i < ArenaWidth /100 + 1; i++)
	{
		FVector Start = TopLeft + FVector(0.f, i * SquareWidth, GridHeight);
		FVector End = Start + FVector(ArenaHeight, 0.f, GridHeight);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);
	}
}

void AGameModeSnake::PlacePointOnGrid()
{
	float GridHeight = 1.f;

	FVector TopLeft = GetBottomPoint();

	for (int32 i = 0; i < ArenaHeight/100; i++)
	{
		for (int32 j = 0; j < ArenaWidth/100; j++)
		{
			FVector UpperLeft = TopLeft + FVector(i * SquareWidth, j * SquareWidth, GridHeight);
			FVector LowerRight = TopLeft + FVector(i * SquareWidth + SquareWidth, j * SquareWidth + SquareWidth, GridHeight);
			FVector RandomPointInSquare = FVector(((UpperLeft.X + LowerRight.X) / 2.0f), ((UpperLeft.Y + LowerRight.Y) / 2.0f), 5.0f);
			DrawDebugPoint(GetWorld(), RandomPointInSquare, 5.f, FColor::Orange, true);
			DrawDebugCircle(GetWorld(), RandomPointInSquare, 25.f, 48, FColor::Purple, true, -1.f, 0, 2.5f, FVector(0.f, 1.f, 0.f), FVector(1.f, 0.f, 0.f), true);
		}
	}
}

void AGameModeSnake::UpdateHUD()
{
	AGameHud* SnakeHud = Cast<AGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (SnakeHud)
	{
		SnakeHud->UpdateCurrentScore(Score);

		if (Score > HighScore)
		{
			HighScore = Score;
			SnakeHud->UpdateHighScore(HighScore);
			//SaveGame();
		}
	}
}

void AGameModeSnake::IncreaseScore()
{
	Score++;
}

void AGameModeSnake::OnSnakeOverlapFood()
{
	ASnake* Snake = Cast<ASnake>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Snake)
	{
		Snake->SpawnTail();
		IncreaseScore(); 
		UpdateHUD(); 
		SpawnFood();
	}
}



