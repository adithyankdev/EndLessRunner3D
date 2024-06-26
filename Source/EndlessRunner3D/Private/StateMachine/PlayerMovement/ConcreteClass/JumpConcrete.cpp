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
	JumpHeight = 450.0f;
	JumpVelocity = FVector::ZeroVector;
	bIsJumping = false; 
	Gravity = -950.0f;
}

JumpConcrete::~JumpConcrete()
{

}
//State Enter // Player Up Function
void JumpConcrete::EnterState(ARunningPlayer* Player, UWorld* World) 
{
   

    bool bHitGround = ULevelManagerFunctionLibrary::LineTraceCheck(World, Player);
 //   PlayerGroundLoc = Player->GetActorLocation().Z;

    if (bHitGround and !bIsJumping)
    {                    
        bIsJumping = true;
        FVector F = FVector{ 0.0f,0.0f,500.0f };
        Player->BoxComp->AddImpulse(F, NAME_None, true);
        // SetActor To MidAir , Give Effect Of Jump .....
      /*  JumpVelocity.Z = JumpHeight;
        bIsJumping = true;
        FVector NewLocation = Player->GetActorLocation() + FVector(0.0f, 0.0f, JumpHeight * 0.13f);
        Player->SetActorLocation(NewLocation);

        // Start the gravity application timer*/
        World->GetTimerManager().SetTimer(ApplyGravityTimer, [this,World]() { this->StopJumping(World); }, 1.3f, true);
    }
}

//Function For Applying Gravity Effect For The Player..
void JumpConcrete::ApplyGravity(ARunningPlayer* Player, UWorld* World) 
{
    if (bIsJumping)
    {

        // Apply gravity to the Z velocity
        JumpVelocity.Z += Gravity * 0.013f;  // Assuming Gravity is negative

        // Update the player's location                                                                // Falling State .....
        FVector NewLocation = Player->GetActorLocation() + JumpVelocity * 0.016f;
        Player->SetActorLocation(NewLocation);

        // Check for collision with the ground
        bool bHitGround = ULevelManagerFunctionLibrary::LineTraceCheck(World, Player);
        if (bHitGround && JumpVelocity.Z <= 0.0f)
        {
        //    StopJumping(Player, World);
        }
    }
}
//Function For Stop Applying the Fall Velocity..
void JumpConcrete::StopJumping(UWorld* World) // Stoping The Applying Gravity 
{
    bIsJumping = false;
    World->GetTimerManager().ClearTimer(ApplyGravityTimer);

}
