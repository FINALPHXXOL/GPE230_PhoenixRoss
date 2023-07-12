// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "Pickup.h"
#include "MazeCharacter.h"

void AHealthPickup::CheckActorType(AActor* OverlappedActor, AActor* OtherActor)
{
	// If the other actor is a maze character
	if (AMazeCharacter* MazeCharacter = Cast<AMazeCharacter>(OtherActor))
	{
		AMazeCharacter* player = MazeCharacter;
		Apply(player);
	}
}

void AHealthPickup::Apply(AMazeCharacter* player)
{
	player->Heal(healAmount);
	APickup::Apply(player);
}

void AHealthPickup::DestroySelf()
{
	this->Destroy();
}

