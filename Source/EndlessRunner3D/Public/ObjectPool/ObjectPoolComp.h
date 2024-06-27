
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/ActorPoolMembers.h"
#include "ObjectPoolComp.generated.h"

class APoolActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDLESSRUNNER3D_API UObjectPoolComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UObjectPoolComp();	

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ObjectPool Base")
	TSubclassOf<AActor>PoolActorClass;

	UPROPERTY()
	TArray<AActor*>PoolActorArray;

	UPROPERTY()
	int PoolSize;

	UPROPERTY(BlueprintReadOnly , EditAnywhere)
	float SingleTileSize;

	UPROPERTY()
	AActor* LatestRearFloor;

	UPROPERTY()
	int QuickSpwanCount;

protected:


	virtual void BeginPlay() override;

	UFUNCTION()
	void InitializePool();

	UFUNCTION(BlueprintCallable)
	AActor* UseFromPool(FVector UseLocation);

	UFUNCTION()
	AActor* GetNotUseActor();

   //HelperFunctions
	UFUNCTION()
	void UpdateLatestRearFloor();

	UFUNCTION()
	void InitializeFirstActor(AActor* SpawnActor);


	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
