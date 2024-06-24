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

	virtual void EnterState(ARunningPlayer* Player, UWorld* World)override;


};
