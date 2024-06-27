// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActorPoolMembers.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActorPoolMembers : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ENDLESSRUNNER3D_API IActorPoolMembers
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool ActorInUse() = 0;
	virtual void TriggerActorInUse() = 0;
};
