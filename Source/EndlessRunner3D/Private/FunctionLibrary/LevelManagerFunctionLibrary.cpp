// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/LevelManagerFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "StateMachine/PlayerMovement/ConcreteClass/SideMoveConcrete.h"
#include "Engine/World.h"



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
	if (CurrentState != NextState)
	{
		CurrentState = NextState;
		CurrentState->EnterState(Player, World);
	}

}

bool ULevelManagerFunctionLibrary::LineTraceCheck(UWorld* World, ARunningPlayer* Player)
{
	FHitResult Hit;
	FVector Start = Player->DirectionArrow->GetComponentLocation();
	FVector End = Start - FVector(0.0f, 0.0f, 50.0f);
	ECollisionChannel TraceChannel = ECC_Visibility;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Player);

	bool OnGround =World->LineTraceSingleByChannel(Hit, Start, End, TraceChannel, Params);
	DrawDebugLine(World, Start, End, FColor::Red, false, 1, 0, 1);
	return OnGround;
}

