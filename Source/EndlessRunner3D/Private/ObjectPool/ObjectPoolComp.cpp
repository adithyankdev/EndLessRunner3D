

#include "ObjectPool/ObjectPoolComp.h"
#include "ObjectPool/PoolActor.h"
#include "Kismet/KismetSystemLibrary.h"


UObjectPoolComp::UObjectPoolComp()
{
	PrimaryComponentTick.bCanEverTick = true;


	QuickSpwanCount = 1;
    PoolSize = 20;
}


void UObjectPoolComp::BeginPlay()
{
	Super::BeginPlay();

	InitializePool();
	
}



void UObjectPoolComp::InitializePool()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (int itr = 0; itr < PoolSize; itr++)
	{
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(PoolActorClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

		if(SpawnActor)
		{
			PoolActorArray.AddUnique(SpawnActor);          

				if (QuickSpwanCount <= 10)
				{  
				  
					if (QuickSpwanCount == 1)
					{
						InitializeFirstActor(SpawnActor);
					}
					else
					{
						UpdateLatestRearFloor();

					}
					

				}
			
			
		}

	}
}

AActor* UObjectPoolComp::UseFromPool(FVector UseLocation)
{
	if(AActor* ActorToUse = GetNotUseActor())
	{

		ActorToUse->SetActorLocation(UseLocation);

		if (ActorToUse->GetClass()->ImplementsInterface(UActorPoolMembers::StaticClass()))
		{
			Cast<IActorPoolMembers>(ActorToUse)->TriggerActorInUse();
			return ActorToUse;
			FString Debug = TEXT("Actor Is Good");
			UKismetSystemLibrary::PrintString(GetWorld(), Debug, true, true, FLinearColor::Yellow, 5);
		}
	}
	else
	{
		FString Debug = TEXT("UseFromPool Function Recived NUll Valid Pointer");
		UKismetSystemLibrary::PrintString(GetWorld(), Debug, true, true, FLinearColor::Red, 5);
	}
	return nullptr;

}

AActor* UObjectPoolComp::GetNotUseActor()
{
	for (AActor* Actors : PoolActorArray)
	{
		if (Actors->GetClass()->ImplementsInterface(UActorPoolMembers::StaticClass()))
		{
			if (!Cast<IActorPoolMembers>(Actors)->ActorInUse())
			{
				return Actors;
			}
		}
	}
	return nullptr;

}


void UObjectPoolComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


//Helper Functions  ....

void UObjectPoolComp::InitializeFirstActor(AActor* SpawnActor)
{
	AActor* CompOwner = GetOwner();
	FVector Origin;
	FVector BoxExtent;
	SpawnActor->GetActorBounds(false, Origin, BoxExtent);
	FString Debug = BoxExtent.ToString();
	UKismetSystemLibrary::PrintString(GetWorld(), Debug, true, true, FLinearColor::Red, 20);
	SingleTileSize = BoxExtent.X * 1.9f;
	if (CompOwner)
	{
		LatestRearFloor = UseFromPool(CompOwner->GetActorLocation());
		QuickSpwanCount++;
	}

}

void UObjectPoolComp::UpdateLatestRearFloor()
{
	FVector Loc = LatestRearFloor->GetActorLocation();
	LatestRearFloor = UseFromPool(FVector(Loc.X - SingleTileSize, Loc.Y, Loc.Z));
	QuickSpwanCount++;
	FString Debug = TEXT("4");
	UKismetSystemLibrary::PrintString(GetWorld(), Debug, true, true, FLinearColor::White, 5);

}
