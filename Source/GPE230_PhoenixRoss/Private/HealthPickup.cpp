// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "Pickup.h"
#include "MazeCharacter.h"
#include "Math/UnrealMathUtility.h"

// check actor when actor overlapped
void AHealthPickup::CheckActorType(AActor* OverlappedActor, AActor* OtherActor)
{
	// If the other actor is a maze character
	if (AMazeCharacter* MazeCharacter = Cast<AMazeCharacter>(OtherActor))
	{
		AMazeCharacter* player = MazeCharacter;

		// Generate a random number between 0 and 1
		float RandomChance = FMath::RandRange(0.0f, 1.0f);

		if (RandomChance <= applyChance) // 75% chance
		{
			Apply(player);
		}
		else // 25% chance
		{
			player->ExecuteStun(stunTime);
			DestroySelf();
		}
	}
}

// apply function
void AHealthPickup::Apply(AMazeCharacter* player)
{
	player->Heal(healAmount);
	APickup::Apply(player);
}

// destroy self function
void AHealthPickup::DestroySelf()
{
	this->Destroy();
}

