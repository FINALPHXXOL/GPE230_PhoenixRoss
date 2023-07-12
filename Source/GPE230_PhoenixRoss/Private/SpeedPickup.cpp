// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedPickup.h"
#include "Pickup.h"
#include "MazeCharacter.h"

void ASpeedPickup::CheckActorType(AActor* OverlappedActor, AActor* OtherActor)
{
	// If the other actor is a maze character
	if (AMazeCharacter* MazeCharacter = Cast<AMazeCharacter>(OtherActor))
	{
		AMazeCharacter* player = MazeCharacter;
		Apply(player);
	}
}

void ASpeedPickup::Apply(AMazeCharacter* player)
{
	player->IncreaseMoveSpeedForTime(speedAmount, speedTime);
	APickup::Apply(player);
}

void ASpeedPickup::DestroySelf()
{
	this->Destroy();
}