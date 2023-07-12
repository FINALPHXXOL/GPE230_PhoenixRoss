// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Engine/SkeletalMesh.h"
#include "Camera/CameraComponent.h"

#include "NiagaraTypes.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "MazeCharacter.generated.h"

UCLASS()
class GPE230_PHOENIXROSS_API AMazeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMazeCharacter();
	UPROPERTY(EditAnywhere)
		float maxHealth;
	UPROPERTY(EditAnywhere)
		float _currentHealth;
	UPROPERTY(EditAnywhere)
		float defaultWalkSpeed;
	UPROPERTY(EditAnywhere)
		float moveSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Die();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual float Heal(float healthToAdd);
	virtual void IncreaseMoveSpeedForTime(float addSpeed, float duration);
	virtual void RevertMoveSpeed();

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
