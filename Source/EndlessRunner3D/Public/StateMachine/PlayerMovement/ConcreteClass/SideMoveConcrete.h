// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunningPlayer/RunningPlayer.h"
#include "StateMachine/PlayerMovement/AbstractClass.h"

/**
 * 
 */
class ENDLESSRUNNER3D_API SideMoveConcrete : public AbstractClass
{
public:
	SideMoveConcrete();
	~SideMoveConcrete();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	int CurrentLane;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	int TotalNumberOfLane;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	float LaneWidth;


	virtual void EnterState(ARunningPlayer* Player, UWorld* World) override;

	void GetLvlValue(UWorld* World);
	bool bGetlvlTrigger;
};
