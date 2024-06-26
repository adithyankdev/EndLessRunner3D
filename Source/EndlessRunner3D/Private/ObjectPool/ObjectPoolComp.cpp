

#include "ObjectPool/ObjectPoolComp.h"
#include "ObjectPool/PoolActor.h"
#include "Kismet/KismetSystemLibrary.h"

UObjectPoolComp::UObjectPoolComp()
{
	PrimaryComponentTick.bCanEverTick = true;


	QuickSpwanCount = 2;
    PoolSize = 5;
}


void UObjectPoolComp::BeginPlay()
{
	Super::BeginPlay();

	InitializePool();
	
}



void UObjectPoolComp::InitializePool()
{
	FActorSpawnParameters SpawnParams;
	AActor* CompOwner = GetOwner();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (int itr = 0; itr < PoolSize; itr++)
	{
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(PoolActorClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

		if(SpawnActor)
		{
			PoolActorArray.AddUnique(SpawnActor);          

				if (PoolActorArray.Num() < QuickSpwanCount)
				{  
				  
					if (PoolActorArray.Num() == 1)
					{
						FVector Origin;
						FVector BoxExtent;
						SpawnActor->GetActorBounds(false,Origin,BoxExtent);
						SingleTileSize = BoxExtent.X * 2.0f; 

						if (CompOwner)
						{
							LatestRearFloor  =  UseFromPool(CompOwner->GetActorLocation());
							QuickSpwanCount++;
							
						}
					}
					

				}
				
			 

			
		}

	}
}

AActor* UObjectPoolComp::UseFromPool(FVector UseLocation)
{


	return nullptr;
}

AActor* UObjectPoolComp::GetNotUseActor()
{
	return nullptr;
}

void UObjectPoolComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

