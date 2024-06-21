
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorLane.generated.h"

UCLASS()
class ENDLESSRUNNER3D_API AFloorLane : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AFloorLane();

protected:
	
	virtual void BeginPlay() override;

public:	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LevelValues")
	int NumberOfLane;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LevelValues")
	float LaneWidth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LevelValues")
	float LevelSpwanningSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LevelValues")
	FVector LevelFloorOutOfBoundBoxLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LevelValues")
	FVector LevelFloorOutOfBoundSize;

	virtual void Tick(float DeltaTime) override;

};
