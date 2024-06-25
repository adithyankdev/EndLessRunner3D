// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunningPlayer/RunningPlayer.h"
#include "StateMachine/PlayerMovement/AbstractClass.h"


/**
 * 
 */
class ENDLESSRUNNER3D_API JumpConcrete : public AbstractClass
{
public:
	JumpConcrete();
	~JumpConcrete();

	//UPROPERTY()
	//FVector FORCE;
	//UPROPERTY()
	//bool bImpulseCaluculation;

	
	//FHitResult Hit;
	//FVector Start;
	//FVector End;
	//ECollisionChannel TraceChannel;
	//FCollisionQueryParams Params;
private:
	FTimerHandle ApplyGravityTimer;

	ARunningPlayer* MainPlayer;
	UWorld* GetWorld;

	bool bIsJumping;
	FVector JumpVelocity;
	float JumpHeight;
	float Gravity;

	virtual void EnterState(ARunningPlayer* Player, UWorld* World)override;

	virtual void ApplyGravity(ARunningPlayer* Player, UWorld* World);
	virtual void StopJumping(ARunningPlayer* Player, UWorld* World);


};
