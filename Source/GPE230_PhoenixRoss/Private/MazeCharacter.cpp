// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"

// Sets default values
AMazeCharacter::AMazeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazeCharacter::BeginPlay()
{
	Super::BeginPlay();

	_controller = Cast<APlayerController>(GetController());

	_currentHealth = maxHealth;

	UCharacterMovementComponent* CharacterMovementU = GetCharacterMovement();
	if (CharacterMovementU)
	{
		defaultWalkSpeed = CharacterMovementU->MaxWalkSpeed;
	}
}

// Declare a timer handle for the duration of the increased move speed
FTimerHandle IncreaseSpeedTimerHandle;

void AMazeCharacter::IncreaseMoveSpeedForTime(float AddSpeed, float Duration)
{
	UCharacterMovementComponent* CharacterMovementU = GetCharacterMovement();
	if (CharacterMovementU)
	{
		// Increase the maximum walk speed
		CharacterMovementU->MaxWalkSpeed += AddSpeed;

		// Set a timer to revert the maximum walk speed after the specified duration
		GetWorldTimerManager().SetTimer(IncreaseSpeedTimerHandle, this, &AMazeCharacter::RevertMoveSpeed, Duration, false);
	}
}

void AMazeCharacter::RevertMoveSpeed()
{
	UCharacterMovementComponent* CharacterMovementU = GetCharacterMovement();
	if (CharacterMovementU)
	{
		// Reset the maximum walk speed to the default value
		CharacterMovementU->MaxWalkSpeed = defaultWalkSpeed;
	}
}

FTimerHandle AnimPlayOut;
FTimerDelegate TimerDelegate;

void AMazeCharacter::WaitBeforePause(float duration)
{
	TimerDelegate.BindUFunction(this, FName("PauseGameplay"), true);
	GetWorldTimerManager().SetTimer(AnimPlayOut, TimerDelegate, duration, false);
}

float AMazeCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!_isDead)
	{
		//Subtract incoming damage
		_currentHealth -= DamageAmount;

		UE_LOG(LogTemp, Log, TEXT("Player took %f damage. %f health remaining. "), DamageAmount, _currentHealth);

		if (_currentHealth <= 0)
		{
			Die();
		}

		return DamageAmount;
	}
	else
		return 0;
}

float AMazeCharacter::Heal(float healthToAdd)
{
	if (_currentHealth < maxHealth)
	{
		//Subtract incoming damage
		_currentHealth += healthToAdd;

		if (_currentHealth > maxHealth)
		{
			_currentHealth = maxHealth;
		}

		UE_LOG(LogTemp, Log, TEXT("Player healed %f damage. %f health remaining. "), healthToAdd, _currentHealth);

		return healthToAdd;
	}
	else
		return 0;
}

void AMazeCharacter::Die()
{
	_isDead = true;
	_currentHealth = 0;
	moveSpeed = 0;
	rotationSpeed = 0;

	GetMesh()->PlayAnimation(_deathAnim, false);
	WaitBeforePause(_deathAnim->GetPlayLength());

	//ToDo: Trigger game over state and prompt the player to restart the level.
	OpenGameOverScreen();
	
}

float AMazeCharacter::GetCurrentHealth()
{
	return _currentHealth;
}


void AMazeCharacter::OpenGameOverScreen()
{
	PauseGameplay(true);
	ShowMouseCursor();
	if (_gameOverScreenTemplate)
	{
		_gameOverScreenInstance = CreateWidget(GetWorld(), _gameOverScreenTemplate);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game Over screen template is null."));
	}

	if (_gameOverScreenInstance)
	{
		_gameOverScreenInstance->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game Over screen instance is null."));
	}
	
}

void AMazeCharacter::OpenVictoryScreen()
{
	PauseGameplay(true);
	ShowMouseCursor();
	if (_victoryScreenTemplate)
	{
		_victoryScreenInstance = CreateWidget(GetWorld(), _victoryScreenTemplate);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Victory screen template is null."));
	}

	if (_victoryScreenInstance)
	{
		_victoryScreenInstance->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Victory screen instance is null."));
	}
}

void AMazeCharacter::PauseGameplay(bool bIsPaused)
{
	_controller->SetPause(bIsPaused);
}

void AMazeCharacter::ShowMouseCursor()
{
	_controller->bShowMouseCursor = true;
}

// Called every frame
void AMazeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMazeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &AMazeCharacter::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &AMazeCharacter::MoveLR);
	PlayerInputComponent->BindAxis(TEXT("Rotate"), this, &AMazeCharacter::Rotate);
}

/*
void AMazeCharacter::MoveFB(float value)
{
	AddMovementInput(GetActorForwardVector(), value * moveSpeed);
}

void AMazeCharacter::MoveLR(float value)
{
	AddMovementInput(-GetActorRightVector(), value * moveSpeed);
}
*/

void AMazeCharacter::MoveFB(float value)
{
	AddMovementInput(GetActorForwardVector(), value * moveSpeed);
}

void AMazeCharacter::MoveLR(float value)
{
	AddMovementInput(-GetActorRightVector(), value * moveSpeed);
}

void AMazeCharacter::Rotate(float value)
{
	AddControllerYawInput(value * rotationSpeed);
}

void AMazeCharacter::ActivateStunParticleSystem()
{
	if (_stunSystem)
	{
		USceneComponent* AttachComp = GetDefaultAttachComponent();

		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(_stunSystem, AttachComp, NAME_None,
			FVector(0), FRotator(0), EAttachLocation::Type::KeepRelativeOffset, true);

		NiagaraComp->Activate();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player attempted to use the stun ability, but no template particle system was found."));
	}
}

