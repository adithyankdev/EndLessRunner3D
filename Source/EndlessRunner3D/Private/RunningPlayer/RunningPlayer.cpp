// Fill out your copyright notice in the Description page of Project Settings.


#include "RunningPlayer/RunningPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "RunningPlayer/RunningPlayerController.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "FunctionLibrary/LevelManagerFunctionLibrary.h"
#include "StateMachine/PlayerMovement/ConcreteClass/SideMoveConcrete.h"


// Sets default values
ARunningPlayer::ARunningPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	SetRootComponent(BoxComp);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	DirectionArrow->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	SideMovetState = new SideMoveConcrete();
}

// Called when the game starts or when spawned
void ARunningPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARunningPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARunningPlayer::MoveAction(const FInputActionValue& InputValue)
{
	LatestSideWayDirection = InputValue.Get<FInputActionValue::Axis1D>();
	ULevelManagerFunctionLibrary::SwitchPlayerState(SideMovetState, CurrentState, this, GetWorld());
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

