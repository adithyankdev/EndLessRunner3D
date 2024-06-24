// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/PlayerMovement/ConcreteClass/JumpConcrete.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

JumpConcrete::JumpConcrete()
{
	//FORCE = {0,0,0};
	//bImpulseCaluculation= true; 
	
}

JumpConcrete::~JumpConcrete()
{

}

void JumpConcrete::EnterState(ARunningPlayer* Player, UWorld* World)
{
	//FVector Direction = Player->DirectionArrow->GetForwardVector();
     //float forcedepth = 5000.0f;
	// FORCE = Direction * forcedepth;
	// Player->BoxComp->AddImpulse(FORCE);

}
