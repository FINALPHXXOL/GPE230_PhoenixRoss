// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryTriggerVolume.h"
#include "MazeCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AVictoryTriggerVolume::AVictoryTriggerVolume()
{
	OnActorBeginOverlap.AddDynamic(this, &AVictoryTriggerVolume::CheckActorType);
}

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

void AVictoryTriggerVolume::OpenVictoryScreen(AMazeCharacter* player)
{
	player->OpenVictoryScreen();
}
