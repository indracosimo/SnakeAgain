// Fill out your copyright notice in the Description page of Project Settings.


#include "UGameDataSubsystem.h"

void UUGameDataSubsystem::SetTwoPlayer(bool bNewTwoPlayer)
{
	bTwoPlayer = bNewTwoPlayer;
}

void UUGameDataSubsystem::SetVsAi(bool bNewVsAI)
{
	bVsAI = bNewVsAI;
}
