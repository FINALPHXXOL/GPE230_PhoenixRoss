// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGameMode.h"

// Init game state
void AMazeGameMode::InitGameState()
{
	Super::InitGameState();

	//If there is no override for the default pawn class
	if (DefaultPawnClass == ADefaultPawn::StaticClass())
	{
		//Set the default pawn to MY pawn
		DefaultPawnClass = DefaultPlayerCharacter;
	}
}

