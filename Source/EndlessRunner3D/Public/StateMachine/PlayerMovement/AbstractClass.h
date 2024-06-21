// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class ARunningPlayer;
/**
 * 
 */
class ENDLESSRUNNER3D_API AbstractClass
{
public:
	AbstractClass();
	virtual~AbstractClass();

	virtual void EnterState(ARunningPlayer* Player, UWorld* World) = 0;
};
