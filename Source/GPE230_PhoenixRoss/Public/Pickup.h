// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class GPE230_PHOENIXROSS_API APickup : public ATriggerBox
{
	GENERATED_BODY()

public:
		APickup();
	UFUNCTION()
		virtual void CheckActorType(class AActor* OverlappedActor, class AActor* OtherActor);
	UPROPERTY(EditAnywhere)
		USoundWave* _pickupSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float applyChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float stunTime;
protected:
	UFUNCTION()
		virtual void Apply(AMazeCharacter* player);
	UFUNCTION()
		virtual void DestroySelf();
};
