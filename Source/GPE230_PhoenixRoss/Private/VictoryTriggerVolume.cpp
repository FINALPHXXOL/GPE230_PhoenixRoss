// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryTriggerVolume.h"
#include "MazeCharacter.h"

void AVictoryTriggerVolume::CheckActorType(AActor* OverlappedActor, AActor* OtherActor)
{
	// If the other actor is a maze character
	if (AMazeCharacter* MazeCharacter = Cast<AMazeCharacter>(OtherActor))
	{
		AMazeCharacter* player = MazeCharacter;
		OpenVictoryScreen(player);
	}
}

void AVictoryTriggerVolume::OpenVictoryScreen(AMazeCharacter* player)
{
	player->OpenVictoryScreen();
}
