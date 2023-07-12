// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "MazeCharacter.h"

APickup::APickup()
{
	OnActorBeginOverlap.AddDynamic(this, &APickup::CheckActorType);
}

void APickup::CheckActorType(class AActor* OverlappedActor, class AActor* OtherActor)
{
	// If the other actor is a maze character
	if (AMazeCharacter* MazeCharacter = Cast<AMazeCharacter>(OtherActor))
	{
		AMazeCharacter* player = MazeCharacter;
		Apply(player);
	}
}

void APickup::Apply(AMazeCharacter* player)
{
	DestroySelf();
}

void APickup::DestroySelf()
{
	this->Destroy();
}

