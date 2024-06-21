// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameBase/FloorLane.h"
#include "LevelManagerFunctionLibrary.generated.h"

class AbstractClass;

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER3D_API ULevelManagerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	static AFloorLane* GetLevelManager(UWorld* GetWorld);
	static void SetLevelInfoOnPlayer(AFloorLane* FloorLane, int& PlayerCurrentLane, float& PlayerLaneWidth, int& PlayerNumberOfLane);
	static void SwitchPlayerState(AbstractClass* NextState, AbstractClass* CurrentState, class ARunningPlayer* Player, UWorld* World);


};
