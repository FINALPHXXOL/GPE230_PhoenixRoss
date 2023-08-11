// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryTriggerVolume.h"
#include "MazeCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Victory Trigger Volume class
AVictoryTriggerVolume::AVictoryTriggerVolume()
{
	OnActorBeginOverlap.AddDynamic(this, &AVictoryTriggerVolume::CheckActorType);
}

// Check Actor for overlap event
void AVictoryTriggerVolume::CheckActorType(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA(AMazeCharacter::StaticClass()))
	{
		// If the other actor is a maze character
		if (AMazeCharacter* MazeCharacter = Cast<AMazeCharacter>(OtherActor))
		{
		//AMazeCharacter* MazeCharacter = Cast<AMazeCharacter>(OtherActor);
		AMazeCharacter* player = MazeCharacter;
		OpenVictoryScreen(player);
		}
	}
}

// opens Victory screen by calling to MazeCharacter
void AVictoryTriggerVolume::OpenVictoryScreen(AMazeCharacter* player)
{
	player->OpenVictoryScreen();
}
