// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RunningPlayer/RunningPlayer.h"
#include "RunningPlayerController.generated.h"

//class ARunningPlayer;

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER3D_API ARunningPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	UPROPERTY()
	class UInputMappingContext* PlayerMappingContext;

	UPROPERTY()
	class UInputAction* MoveInput;

	virtual void BeginPlay() override; 
	
	ARunningPlayer* PlayerCharacter;

};
