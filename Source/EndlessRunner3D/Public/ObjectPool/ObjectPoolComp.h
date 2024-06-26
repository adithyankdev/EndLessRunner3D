
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComp.generated.h"

class APoolActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDLESSRUNNER3D_API UObjectPoolComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UObjectPoolComp();

public:

	UPROPERTY(BlueprintReadWrite , EditDefaultsOnly , Category = "ObjectPool Base")
	TSubclassOf<AActor>PoolActorClass;

	UPROPERTY()
	TArray<AActor*>PoolActorArray;

	UPROPERTY()
	int PoolSize;

	UPROPERTY()
	float SingleTileSize;

	UPROPERTY()
	AActor* LatestRearFloor;

	UPROPERTY()
	int QuickSpwanCount;

	virtual void BeginPlay() override;

public:	

	UFUNCTION()
	void InitializePool();

	UFUNCTION()
	AActor* UseFromPool(FVector UseLocation);

	UFUNCTION()
	AActor* GetNotUseActor();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
