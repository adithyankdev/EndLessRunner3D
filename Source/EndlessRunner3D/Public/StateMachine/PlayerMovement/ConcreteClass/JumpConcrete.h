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

private:

	//Timer For Handling ApplyGravity to Player...
	FTimerHandle ApplyGravityTimer;

	
	bool bIsJumping;
	FVector JumpVelocity;
	float JumpHeight;
	float Gravity;
	float PlayerGroundLoc;

	virtual void EnterState(ARunningPlayer* Player, UWorld* World)override;
	virtual void ApplyGravity(ARunningPlayer* Player, UWorld* World);
	virtual void StopJumping(UWorld* World);


};
