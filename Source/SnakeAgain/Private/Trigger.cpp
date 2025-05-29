// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeAgain/Public/Trigger.h"
#include "SnakeAgain/Public/Snake.h"


// Sets default values
ATrigger::ATrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void ATrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ASnake* OverlappedActorAsSnake = Cast<ASnake>(OtherActor);
	if (OverlappedActorAsSnake)
	{
		OverlapedWithSnakeHead(OverlappedActorAsSnake);
	}
}

