// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "MazeCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"
#include "Math/UnrealMathUtility.h"

// Pickup class
APickup::APickup()
{
	OnActorBeginOverlap.AddDynamic(this, &APickup::CheckActorType);
}

// Check Actor function
void APickup::CheckActorType(class AActor* OverlappedActor, class AActor* OtherActor)
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

// Apply class
void APickup::Apply(AMazeCharacter* player)
{
	UGameplayStatics::PlaySound2D(player, _pickupSound);
	DestroySelf();
}

// Destroy self functions
void APickup::DestroySelf()
{
	this->Destroy();
}

