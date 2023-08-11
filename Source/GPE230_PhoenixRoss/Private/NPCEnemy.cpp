// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCEnemy.h"
#include "MazeCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Sound/SoundWave.h"

// Sets default values
ANPCEnemy::ANPCEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Detects hit
void ANPCEnemy::DetectHit()
{
	bool canDamage = true;

	// Get location of the fist
	const FVector PunchLocation = GetMesh()->GetSocketLocation(_PunchingHandSocketName);

	// Don't detct this actor or its controller in the spheretrace
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(GetOwner());

	// Array for actors hit by the spheretrace
	TArray<FHitResult> HitArray;

	// Spheretrace around fist for overlapped actors = true if there are any, false if there are none
	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), PunchLocation, PunchLocation, _TraceRadius,
		UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::None, HitArray,
		true, FLinearColor::Red, FLinearColor::Green, 2.0f);

	// None of this actor (for debugging)
	FString ownerName = this->GetName();

	// If there is a valid hit
	if (Hit)
	{
		for (const FHitResult HitResult : HitArray)
		{
			if (canDamage)
			{
				if (AMazeCharacter* HitMazeCharacter = Cast<AMazeCharacter>(HitResult.GetActor()))
				{
					FString hitActorName = HitResult.GetActor()->GetName();

					//UE_LOG(LogTemp, Log, TEXT("NPCEnemy actor \"%s\" hit other actor \"%s\", dealing %f damage."), *ownerName, *hitActorName, _HitDamage);

					// Apply damage to the hit actor
					UGameplayStatics::ApplyDamage(HitMazeCharacter, _HitDamage, GetController(), this, UDamageType::StaticClass());
					UGameplayStatics::PlaySound2D(this, _punchSound);

					canDamage = false;
				}
			}
		}
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("NPCEnemy actor \"%s\" did not detect any valid hits on its last attack."), *ownerName);
	}
}

// Called every frame
void ANPCEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

