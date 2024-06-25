// Fill out your copyright notice in the Description page of Project Settings.


#include "RunningPlayer/RunningPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "RunningPlayer/RunningPlayerController.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "FunctionLibrary/LevelManagerFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameBase/FloorLane.h"
//Movement StateMachines Header.........
#include "StateMachine/PlayerMovement/ConcreteClass/SideMoveConcrete.h"
#include "StateMachine/PlayerMovement/ConcreteClass/JumpConcrete.h"


// Sets default values
ARunningPlayer::ARunningPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.....
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = BoxComp;
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	DirectionArrow->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	SideMovetState = new SideMoveConcrete();
	JumpState = new JumpConcrete();
	
}

// Called when the game starts or when spawned......
void ARunningPlayer::BeginPlay()
{
	Super::BeginPlay();

	 AFloorLane* Flr =  ULevelManagerFunctionLibrary::GetLevelManager(GetWorld());

}

// Called every frame.....
void ARunningPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugLine(GetWorld(), GetActorLocation() ,GetActorLocation() + DirectionArrow->GetUpVector()*-1200, FColor::Red, true);


}

void ARunningPlayer::MoveAction(const FInputActionValue& InputValue)
{
	LatestSideWayDirection = InputValue.Get<FInputActionValue::Axis1D>();
	
		ULevelManagerFunctionLibrary::SwitchPlayerState(SideMovetState, CurrentState, this, GetWorld());
	
	 
}

void ARunningPlayer::JumpAction(const FInputActionValue& InputValue)
{
	if (ULevelManagerFunctionLibrary::LineTraceCheck(GetWorld(), this))
	{
		ULevelManagerFunctionLibrary::SwitchPlayerState(JumpState, CurrentState, this, GetWorld());
	}
	
}
// Called to bind functionality to input
void ARunningPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	ARunningPlayerController* PlayerController = Cast<ARunningPlayerController>(Controller);

	check(EnhancedInputComp and PlayerController)
	{
		EnhancedInputComp->BindAction(PlayerController->MoveInput, ETriggerEvent::Started, this, &ARunningPlayer::MoveAction);
		EnhancedInputComp->BindAction(PlayerController->JumpInput, ETriggerEvent::Completed, this, &ARunningPlayer::JumpAction);

		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		check(LocalPlayer)
		{
			UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

			check(Subsystem)
			{
				Subsystem->ClearAllMappings();
				Subsystem->AddMappingContext(PlayerController->PlayerMappingContext, 0);
			}
		}
	}
}

