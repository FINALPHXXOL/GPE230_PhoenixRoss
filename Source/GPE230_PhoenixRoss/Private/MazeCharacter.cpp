// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Engine/World.h"
#include "Sound/SoundWave.h"

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
		defaultMoveSpeed = moveSpeed;
		defaultRotationSpeed = rotationSpeed;
	}
}

// Declare a timer handle for the duration of the increased move speed
FTimerHandle IncreaseSpeedTimerHandle;

//Increases Movement Speed for a time
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

// Reverts movement speed
void AMazeCharacter::RevertMoveSpeed()
{
	UCharacterMovementComponent* CharacterMovementU = GetCharacterMovement();
	if (CharacterMovementU)
	{
		// Reset the maximum walk speed to the default value
		CharacterMovementU->MaxWalkSpeed = defaultWalkSpeed;
	}
}

FTimerHandle StunAnimPlayOut;

// Stuns the player for a tiem
void AMazeCharacter::ExecuteStun(float duration)
{
	moveSpeed = 0;
	rotationSpeed = 0;
	UGameplayStatics::PlaySound2D(this, _stunSound);
	GetMesh()->PlayAnimation(_stunAnim, true);
	// Set the timer to call the custom function after the specified duration
	GetWorldTimerManager().SetTimer(StunAnimPlayOut, this, &AMazeCharacter::ExecuteUnstun, duration, false);
}

// Reverts the stun
void AMazeCharacter::ExecuteUnstun()
{
	// This function will be called after the timer expires
	if (_isDead == false)
	{
		moveSpeed = defaultMoveSpeed;
		rotationSpeed = defaultRotationSpeed;
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	}
}

FTimerHandle AnimPlayOut;
//FTimerDelegate TimerDelegate;

// When player dies, this function plays for however long the death animation is.
void AMazeCharacter::WaitBeforePause(float duration)
{
	// Set the timer to call the custom function after the specified duration
	GetWorldTimerManager().SetTimer(AnimPlayOut, this, &AMazeCharacter::ExecutePause, duration, false);
}

// Opens the Game Over Screen after death animation ends.
void AMazeCharacter::ExecutePause()
{
	// This function will be called after the timer expires
	OpenGameOverScreen();
}

// function for taking damage.
float AMazeCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!_isDead)
	{
		//Subtract incoming damage
		_currentHealth -= DamageAmount;

		//UE_LOG(LogTemp, Log, TEXT("Player took %f damage. %f health remaining. "), DamageAmount, _currentHealth);

		if (_currentHealth <= 0)
		{
			Die();
		}

		return DamageAmount;
	}
	else
		return 0;
}

// function for healing.
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

		//UE_LOG(LogTemp, Log, TEXT("Player healed %f damage. %f health remaining. "), healthToAdd, _currentHealth);

		return healthToAdd;
	}
	else
		return 0;
}

// function for when health drops to 0.
void AMazeCharacter::Die()
{
	_isDead = true;
	_currentHealth = 0;
	moveSpeed = 0;
	rotationSpeed = 0;

	GetMesh()->PlayAnimation(_deathAnim, false);
	WaitBeforePause(_deathAnim->GetPlayLength());

	//ToDo: Trigger game over state and prompt the player to restart the level.
	
	
}

// returns Current Health
float AMazeCharacter::GetCurrentHealth()
{
	return _currentHealth;
}

// Opens Game Over Screen
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
		//UE_LOG(LogTemp, Error, TEXT("Game Over screen template is null."));
	}

	if (_gameOverScreenInstance)
	{
		_gameOverScreenInstance->AddToViewport();
	}
	else
	{
		//UE_LOG(LogTemp, Error, TEXT("Game Over screen instance is null."));
	}
	
}

// Opens Victory Screen
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
		//UE_LOG(LogTemp, Error, TEXT("Victory screen template is null."));
	}

	if (_victoryScreenInstance)
	{
		_victoryScreenInstance->AddToViewport();
	}
	else
	{
		//UE_LOG(LogTemp, Error, TEXT("Victory screen instance is null."));
	}
}

// Pauses Gameplay
void AMazeCharacter::PauseGameplay(bool bIsPaused)
{
	_controller->SetPause(bIsPaused);
}

// Shows Mouse Cursor
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

// Move Forward/backward input
void AMazeCharacter::MoveFB(float value)
{
	AddMovementInput(GetActorForwardVector(), value * moveSpeed);
}
// move left/right input
void AMazeCharacter::MoveLR(float value)
{
	AddMovementInput(-GetActorRightVector(), value * moveSpeed);
}

//rotates using mouse or right analog stick
void AMazeCharacter::Rotate(float value)
{
	AddControllerYawInput(value * rotationSpeed);
}

// manages stun particle system
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
		//UE_LOG(LogTemp, Error, TEXT("Player attempted to use the stun ability, but no template particle system was found."));
	}
}

