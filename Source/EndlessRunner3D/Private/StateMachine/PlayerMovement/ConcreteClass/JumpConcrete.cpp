// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/PlayerMovement/ConcreteClass/JumpConcrete.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "FunctionLibrary/LevelManagerFunctionLibrary.h"

JumpConcrete::JumpConcrete()
{
	//FORCE = {0,0,0};
	//bImpulseCaluculation= true; 
	JumpHeight = 500.0f;
	JumpVelocity = FVector::ZeroVector;
	bIsJumping = false; 
	Gravity = -980.0f;
}

JumpConcrete::~JumpConcrete()
{

}

void JumpConcrete::EnterState(ARunningPlayer* Player, UWorld* World)
{
	MainPlayer = Player;
	GetWorld = World;
	//FVector Direction = Player->DirectionArrow->GetForwardVector();
     //float forcedepth = 5000.0f;
	// FORCE = Direction * forcedepth;
	// Player->BoxComp->AddImpulse(FORCE);
	JumpVelocity.Z = JumpHeight;
	bIsJumping = true;
	FVector NewLocation = MainPlayer->GetActorLocation() + FVector(0.0f,0.0f,JumpHeight * 0.01 );
	Player->SetActorLocation(NewLocation);
	        
	World->GetTimerManager().SetTimer(ApplyGravityTimer, [this,Player,World](){ this->ApplyGravity(Player,World); }, 0.01f, true);
	//TimerManager.SetTimer(ApplyGravityTimer,)
}

void JumpConcrete::ApplyGravity(ARunningPlayer* Player, UWorld* World)
{
	if (bIsJumping)
	{
		JumpVelocity.Z += Gravity;
		FVector NewLocation = Player->GetActorLocation() + JumpVelocity * 0.01f;
		Player->SetActorLocation(NewLocation);

		if (ULevelManagerFunctionLibrary::LineTraceCheck(World,Player) && JumpVelocity.Z <= 0.0f)
		{
			StopJumping(Player, World);
		}
	}
}

void JumpConcrete::StopJumping(ARunningPlayer* Player, UWorld* World)
{
	bIsJumping = false; 
	JumpVelocity = FVector::ZeroVector;
	World->GetTimerManager().ClearTimer(ApplyGravityTimer);

}
