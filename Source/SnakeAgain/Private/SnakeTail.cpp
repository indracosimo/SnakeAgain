// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeAgain/Public/SnakeTail.h"


// Sets default values
ASnakeTail::ASnakeTail()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Mesh->SetRelativeScale3D(FVector(0.5f));
}

void ASnakeTail::BeginPlay()
{
	Super::BeginPlay();
	
}


