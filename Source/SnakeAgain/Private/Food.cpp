// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeAgain/Public/Food.h"
#include "SnakeAgain/Public/GameModeSnake.h"
#include "SnakeAgain/Public/SnakeTail.h"


AFood::AFood()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionObjectType(ECC_Pawn);
	Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AFood::OverlappedWithSnakeHead(class ASnake* Snake)
{
	Destroy();
	AGameModeSnake* GameMode = Cast<AGameModeSnake>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->OnSnakeOverlapFood();
	}
	
}

void AFood::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(ASnakeTail::StaticClass()))
	{
		AGameModeSnake* GameMode = Cast<AGameModeSnake>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->SpawnFood();
		}

		Destroy();
	}
}


