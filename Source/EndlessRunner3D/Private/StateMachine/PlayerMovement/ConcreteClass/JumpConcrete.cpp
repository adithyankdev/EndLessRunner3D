// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/PlayerMovement/ConcreteClass/JumpConcrete.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "FunctionLibrary/LevelManagerFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

//Constructor Of State
JumpConcrete::JumpConcrete()
{
	bIsJumping = false; 
	
}

JumpConcrete::~JumpConcrete()
{

}
void JumpConcrete::EnterState(ARunningPlayer* Player, UWorld* World) 
{
   
    bool bHitGround = ULevelManagerFunctionLibrary::LineTraceCheck(World, Player);

    if (bHitGround and !bIsJumping)
    {                    
        bIsJumping = true;
        FVector F = FVector{ 0.0f,0.0f,500.0f };
        Player->BoxComp->AddImpulse(F, NAME_None, true);
        World->GetTimerManager().SetTimer(ApplyGravityTimer, [this,World]() { this->StopJumping(World); }, 1.3f, true);
    }
}

//Function For Stop Rest The bIsJumping..
void JumpConcrete::StopJumping(UWorld* World) 
{
    bIsJumping = false;
    World->GetTimerManager().ClearTimer(ApplyGravityTimer);

}
