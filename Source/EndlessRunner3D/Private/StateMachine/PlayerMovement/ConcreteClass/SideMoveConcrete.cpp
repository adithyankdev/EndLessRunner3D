// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/PlayerMovement/ConcreteClass/SideMoveConcrete.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FunctionLibrary/LevelManagerFunctionLibrary.h"

SideMoveConcrete::SideMoveConcrete()
{
	bGetlvlTrigger = true;
}

SideMoveConcrete::~SideMoveConcrete()
{
}

void SideMoveConcrete::EnterState(ARunningPlayer* Player, UWorld* World)
{
	if (bGetlvlTrigger == true)GetLvlValue(World); bGetlvlTrigger = false;
	//float val = InputValue.Get<FInputActionValue::Axis1D>();
	if (Player->LatestSideWayDirection > 0 and CurrentLane < TotalNumberOfLane)
	{
		float TargetPosition = Player->GetActorLocation().Y + LaneWidth;
		FVector NewLocation = { Player->GetActorLocation().X , TargetPosition ,Player->GetActorLocation().Z };
		Player->SetActorLocation(NewLocation);
		CurrentLane++;
		FString D = "Triggered";
		UKismetSystemLibrary::PrintString(World, D);
	}
	else if (Player->LatestSideWayDirection < 0 and (CurrentLane > 1))
	{
		float  TargetPosition = Player->GetActorLocation().Y - LaneWidth;
		FVector NewLocation = { Player->GetActorLocation().X , TargetPosition , Player->GetActorLocation().Z };
		Player->SetActorLocation(NewLocation);
		CurrentLane--;
		FString D = "Triggered";
		UKismetSystemLibrary::PrintString(World, D,true,true,FLinearColor::Red);
	}
}

void SideMoveConcrete::GetLvlValue(UWorld* World)
{
	AFloorLane* FloorLane = ULevelManagerFunctionLibrary::GetLevelManager(World);
	ULevelManagerFunctionLibrary::SetLevelInfoOnPlayer(FloorLane, CurrentLane, LaneWidth, TotalNumberOfLane);

	FString D = FString::FromInt(LaneWidth);
	UKismetSystemLibrary::PrintString(World, D, true, true, FLinearColor::Yellow);
}
