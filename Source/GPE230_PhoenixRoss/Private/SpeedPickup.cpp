// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedPickup.h"
#include "Pickup.h"
#include "MazeCharacter.h"
#include "Math/UnrealMathUtility.h"

//Check for specific actor
void ASpeedPickup::CheckActorType(AActor* OverlappedActor, AActor* OtherActor)
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
void ASpeedPickup::Apply(AMazeCharacter* player)
{
	player->IncreaseMoveSpeedForTime(speedAmount, speedTime);
	APickup::Apply(player);
}

// destroy self function
void ASpeedPickup::DestroySelf()
{
	this->Destroy();
}