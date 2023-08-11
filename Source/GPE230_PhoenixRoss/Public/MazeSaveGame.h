// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MazeSaveGame.generated.h"

/*
SaveGame Class
 */
UCLASS()
class GPE230_PHOENIXROSS_API UMazeSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UMazeSaveGame();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int furthestCompletedLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int lastCompletedLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float masterVolumeSetting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float musicVolumeSetting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float sfxVolumeSetting;

protected:

};
