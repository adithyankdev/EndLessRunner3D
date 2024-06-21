// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/LevelManagerFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "StateMachine/PlayerMovement/ConcreteClass/SideMoveConcrete.h"



AFloorLane* ULevelManagerFunctionLibrary::GetLevelManager(UWorld* GetWorld)
{

	TArray<AActor*>FoundActor;

	UGameplayStatics::GetAllActorsOfClass(GetWorld, AFloorLane::StaticClass(), FoundActor);

	if (FoundActor.Num() > 0)
	{
		AFloorLane* Floor = Cast<AFloorLane>(FoundActor[0]);
		return Floor;

	}
	return NULL;
}

void ULevelManagerFunctionLibrary::SetLevelInfoOnPlayer(AFloorLane* FloorLane, int& PlayerCurrentLane, float& PlayerLaneWidth, int& PlayerNumberOfLane)
{
	if (FloorLane)
	{
		PlayerCurrentLane = (FloorLane->NumberOfLane / 2) + 1;
		PlayerLaneWidth = FloorLane->LaneWidth;
		PlayerNumberOfLane = FloorLane->NumberOfLane;
	}
}

void ULevelManagerFunctionLibrary::SwitchPlayerState(AbstractClass* NextState, AbstractClass* CurrentState, ARunningPlayer* Player, UWorld* World)
{
	CurrentState = NextState;
	CurrentState->EnterState(Player, World);
}

