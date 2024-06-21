// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingFloorTile.generated.h"

UCLASS()
class ENDLESSRUNNER3D_API AMovingFloorTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingFloorTile();

protected:
 
	virtual void BeginPlay() override;

	UPROPERTY()
	float LvlSpwanSpeed;

	UFUNCTION()
	void GetLvlManagerValue();

	UFUNCTION()
	void MoveFunction(float DeltaTime);

	

public:	
	
	virtual void Tick(float DeltaTime) override;

};
