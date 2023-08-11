// Fill out your copyright notice in the Description page of Project Settings.

#include "LockAndKey.h"
#include "MazeCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"

// LockAndKey class
ALockAndKey::ALockAndKey()
{
	OnActorBeginOverlap.AddDynamic(this, &ALockAndKey::CheckActorType);
}

/// <summary>
/// Check if the other actor in this trigger is a MazeCharacter. If it is, open the door.
/// </summary>
/// <param name="OverlappedActor"></param>
/// <param name="OtherActor"></param>
void ALockAndKey::CheckActorType(class AActor* OverlappedActor, class AActor* OtherActor)
{
	//If the other actor is a maze character
	if (OtherActor->IsA(AMazeCharacter::StaticClass()))
	{
		UGameplayStatics::PlaySound2D(OtherActor, _doorSound);
		OpenTheDoor();
	}
}

// opens door function
void ALockAndKey::OpenTheDoor()
{
	this->Destroy();
}



