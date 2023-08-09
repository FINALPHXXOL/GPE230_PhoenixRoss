// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Engine/SkeletalMesh.h"
#include "Camera/CameraComponent.h"

#include "NiagaraTypes.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "Blueprint/UserWidget.h"

#include "MazeCharacter.generated.h"

UCLASS()
class GPE230_PHOENIXROSS_API AMazeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMazeCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float maxHealth;
	UPROPERTY(EditAnywhere)
		float _currentHealth;
	UPROPERTY(EditAnywhere)
		float defaultWalkSpeed;
	UPROPERTY(EditAnywhere)
		float moveSpeed;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> _gameOverScreenTemplate;
	UUserWidget* _gameOverScreenInstance;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> _victoryScreenTemplate;
	UUserWidget* _victoryScreenInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Die();
	virtual void OpenGameOverScreen();
	virtual void PauseGameplay(bool bIsPaused);
	virtual void ShowMouseCursor();

	APlayerController* _controller;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual float Heal(float healthToAdd);
	virtual void IncreaseMoveSpeedForTime(float addSpeed, float duration);
	virtual void WaitBeforePause(float duration);
	virtual void ExecuteAfterTimer();
	virtual void RevertMoveSpeed();
	virtual void OpenVictoryScreen();
	UFUNCTION(BlueprintCallable)
		float GetCurrentHealth();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private: 
	
	UPROPERTY(EditAnywhere)
		float rotationSpeed;
	UPROPERTY(EditAnywhere)
		UAnimSequence* _deathAnim;
	UPROPERTY(EditAnywhere)
		bool _isDead = false;
	UPROPERTY(EditAnywhere)
		UNiagaraSystem* _stunSystem;

private:
	void MoveFB(float value);
	void MoveLR(float value);
	void Rotate(float value);
	UFUNCTION(BlueprintCallable)
		void ActivateStunParticleSystem();
};
