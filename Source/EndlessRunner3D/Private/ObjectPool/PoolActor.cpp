


#include "ObjectPool/PoolActor.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"



APoolActor::APoolActor()
{
 
	PrimaryActorTick.bCanEverTick = true;
	TimeToLive = 60.0f;
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
		GetWorld()->GetTimerManager().SetTimer(StopUsingTimer, this, &APoolActor::SetNotUse, TimeToLive);
	}
}

void APoolActor::SetNotUse()
{
	SetInUse(false);
}

void APoolActor::BeginPlay()
{
	Super::BeginPlay();
	SetInUse(false);
	
}


void APoolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


//Interface Functions ... 

bool APoolActor::ActorInUse()
{
	return CurrentlyUse;
}

void APoolActor::TriggerActorInUse()
{
	SetInUse(true);
}
