// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeAgain/Public/Snake.h"
#include "SnakeAgain/Public/GameModeSnake.h"
#include "SnakeAgain/Public/SnakeTail.h"



// Sets default values
ASnake::ASnake()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// set root component
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComp);

	// set mesh
	HeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadMesh"));
	HeadMesh->SetupAttachment(RootComp);
	HeadMesh->SetRelativeScale3D(FVector(0.9f));
	HeadMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HeadMesh->SetCollisionObjectType(ECC_Pawn);
	HeadMesh->SetCollisionResponseToAllChannels(ECR_Overlap);

	// set movement
	MoveDirection = FVector(0.0f);
	MoveStepSize = 50.0f;
	bIsMoving = false;
	bIsAlive = true;
}

// Called when the game starts or when spawned
void ASnake::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AGameModeSnake>(GetWorld()->GetAuthGameMode());
	check(GameMode);

	MoveStepSize = HeadMesh->GetStaticMesh()->GetBoundingBox().GetSize().X;

	// Looping timer for the snake movement
	FTimerHandle TimerHandle_AttackDelay;
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "MoveSnake");

	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, Delegate, 0.15f, true);
	
}

void ASnake::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveUpAction, ETriggerEvent::Triggered, this, &ASnake::MoveUp);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ASnake::MoveRight);
	}
	
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (PC->GetLocalPlayer()->GetControllerId() == 0)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
			else if (PC->GetLocalPlayer()->GetControllerId() == 1)
			{
				Subsystem->AddMappingContext(P2MappingContext, 1);
			}
		}
	}
}

void ASnake::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (OtherActor->IsA(ASnakeTail::StaticClass()))
	{
		if (GameMode && !GameMode->bIsGodModeEnabled)
		{
			UE_LOG(LogTemp, Warning, TEXT("Snake overlapped tail"));
			SetIsAlive(false);
			//GameMode->StopPlayingMusic();
			GameMode->GameOver();
		}
	}
}

void ASnake::MoveSnake()
{
	if (!bIsAlive)
	{
		// Clear timer when the snake dies
		GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);
		return;
	}

	// Move Snake Head
	FVector OldLocation = HeadMesh->GetComponentLocation();
	FRotator OldRotation = HeadMesh->GetComponentRotation();

	AddActorWorldOffset(MoveDirection * MoveStepSize );
	bIsMoving = true;

	//move tail
	for (int i = 0; i < Tails.Num(); i++)
	{
		FVector CurrentLocation = Tails[i]->GetActorLocation();
		FRotator CurrentRotation = Tails[i]->GetActorRotation();

		Tails[i]->SetActorLocation(OldLocation);
		Tails[i]->SetActorRotation(OldRotation);

		OldLocation = CurrentLocation;
		OldRotation = CurrentRotation;
	}
}

void ASnake::MoveUp(const FInputActionValue& Value)
{
	const float AxisValue = Value.Get<float>();
	if (AxisValue > 0.0f)
	{
		MoveDirection = FVector(1.0f, 0.0f, 0.0f);
	}
	else if (AxisValue < 0.0f)
	{
		MoveDirection = FVector(-1.0f, 0.0f, 0.0f);
	}
}

void ASnake::MoveRight(const FInputActionValue& Value)
{
	const float AxisValue = Value.Get<float>();
	if (AxisValue > 0.0f)
	{
		MoveDirection = FVector(0.0f, 1.0f, 0.0f); 
	}
	else if (AxisValue < 0.0f)
	{
		MoveDirection = FVector(0.0f, -1.0f, 0.0f);
	}
}

void ASnake::SpawnTail()
{
	const FVector TailSpawnLocation = (Tails.IsEmpty() ? HeadMesh->GetComponentLocation() : Tails.Last()->GetActorLocation()) - (MoveDirection * MoveStepSize);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ASnakeTail* NewTail = GetWorld()->SpawnActor<ASnakeTail>(DefaultTailClass, TailSpawnLocation, FRotator(), SpawnParams);

	if (NewTail)
	{
		Tails.Add(NewTail);
	}
}

void ASnake::SetIsAlive(bool inBIsAlive)
{
	bIsAlive = inBIsAlive;
}