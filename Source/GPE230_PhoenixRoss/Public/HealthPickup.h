// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class GPE230_PHOENIXROSS_API AHealthPickup : public APickup
{
	GENERATED_BODY()

public:
		virtual void CheckActorType(class AActor* OverlappedActor, class AActor* OtherActor);
	UPROPERTY(EditAnywhere)
		float healAmount;
protected:
		virtual void Apply(AMazeCharacter* player) override;
		virtual void DestroySelf();
};
