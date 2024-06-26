


#include "ObjectPool/PoolActor.h"
#include "TimerManager.h"


APoolActor::APoolActor()
{
 
	PrimaryActorTick.bCanEverTick = true;

}


void APoolActor::SetInUse(bool InUse)
{
	CurrentlyUse = InUse; 
	SetActorTickEnabled(InUse);
	SetActorEnableCollision(InUse);
	SetActorHiddenInGame(!InUse);

	GetWorld()->GetTimerManager().ClearTimer(StopUsingTimer);
	if (InUse)
	{
		GetWorld()->GetTimerManager().SetTimer(StopUsingTimer, this, &APoolActor::SetNotUse, 5);
	}
}

void APoolActor::SetNotUse()
{
	SetInUse(true);
}

void APoolActor::BeginPlay()
{
	Super::BeginPlay();
	
}


void APoolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

