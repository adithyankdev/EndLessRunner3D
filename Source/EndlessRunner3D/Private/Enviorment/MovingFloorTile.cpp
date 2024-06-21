// Fill out your copyright notice in the Description page of Project Settings.


#include "Enviorment/MovingFloorTile.h"
#include "FunctionLibrary/LevelManagerFunctionLibrary.h"
#include "GameBase/FloorLane.h"



// Sets default values
AMovingFloorTile::AMovingFloorTile()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingFloorTile::BeginPlay()
{
	Super::BeginPlay();
	GetLvlManagerValue();
}

// Called every frame
void AMovingFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveFunction(DeltaTime);

}
void AMovingFloorTile::GetLvlManagerValue()
{
	AFloorLane* Floor = ULevelManagerFunctionLibrary::GetLevelManager(GetWorld());
	LvlSpwanSpeed = Floor->LevelSpwanningSpeed;
}

void AMovingFloorTile::MoveFunction(float DeltaTime)
{
	FVector ChangeInLoc = (GetOwner()->GetActorForwardVector() * LvlSpwanSpeed) * DeltaTime;
	GetOwner()->AddActorLocalOffset(ChangeInLoc, false);
}



