// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBase/FloorLane.h"

// Sets default values
AFloorLane::AFloorLane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloorLane::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorLane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

