

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ActorPoolMembers.h"
#include "PoolActor.generated.h"

UCLASS()
class ENDLESSRUNNER3D_API APoolActor : public AActor , public IActorPoolMembers
{
	GENERATED_BODY()
	
public:	
	
	APoolActor();

	virtual bool ActorInUse()override;
	virtual void TriggerActorInUse()override;

protected:
    
	UPROPERTY()
	bool CurrentlyUse;

	UPROPERTY()
	float TimeToLive;

	FTimerHandle StopUsingTimer; 

	UFUNCTION()
	void SetInUse(bool InUse);

	UFUNCTION()
	void SetNotUse();
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
