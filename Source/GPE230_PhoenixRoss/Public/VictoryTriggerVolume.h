// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "VictoryTriggerVolume.generated.h"

/**
 Victory trigger volume class.
 */
UCLASS()
class GPE230_PHOENIXROSS_API AVictoryTriggerVolume : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	AVictoryTriggerVolume();
	UFUNCTION()
		void CheckActorType(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
		void OpenVictoryScreen(AMazeCharacter* player);
};
