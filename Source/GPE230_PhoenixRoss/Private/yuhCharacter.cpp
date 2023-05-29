// Fill out your copyright notice in the Description page of Project Settings.


#include "yuhCharacter.h"

// Sets default values
AyuhCharacter::AyuhCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AyuhCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AyuhCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AyuhCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

