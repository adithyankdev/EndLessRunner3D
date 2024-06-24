// Fill out your copyright notice in the Description page of Project Settings.


#include "RunningPlayer/RunningPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "RunningPlayer/RunningPlayerController.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "FunctionLibrary/LevelManagerFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameBase/FloorLane.h"
//Movement StateMachines Header
#include "StateMachine/PlayerMovement/ConcreteClass/SideMoveConcrete.h"
#include "StateMachine/PlayerMovement/ConcreteClass/JumpConcrete.h"


// Sets default values
ARunningPlayer::ARunningPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	
	JumpHeight = 450.0f; // Adjust this value as needed
	Gravity = -1000.0f; // Gravity value, adjust as needed

	bIsJumping = false;
	JumpVelocity = FVector::ZeroVector;
	count = 0;

}

// Called when the game starts or when spawned
void ARunningPlayer::BeginPlay()
{
	Super::BeginPlay();

	 AFloorLane* Flr =  ULevelManagerFunctionLibrary::GetLevelManager(GetWorld());
	 speed = Flr->LevelSpwanningSpeed;
	 Gravity *= 0.01f;

}

// Called every frame
void ARunningPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//AddMovementInput(DirectionArrow->GetForwardVector(), 0.1);
	// 
	// 
	//FVector ChangeInLoc = ((GetActorForwardVector()*-1) * speed) * DeltaTime;
	//AddActorLocalOffset(ChangeInLoc, false);
	DrawDebugLine(GetWorld(), GetActorLocation() ,GetActorLocation() + DirectionArrow->GetUpVector()*-1200, FColor::Red, true);


}

void ARunningPlayer::MoveAction(const FInputActionValue& InputValue)
{
	LatestSideWayDirection = InputValue.Get<FInputActionValue::Axis1D>();
	
		ULevelManagerFunctionLibrary::SwitchPlayerState(SideMovetState, CurrentState, this, GetWorld());
	
	 
}

void ARunningPlayer::JumpAction(const FInputActionValue& InputValue)
{
	

	if (IsOnGround())
	{
		/*float forcedepth = 500.0f;
		FVector FORCE = FVector{0.0f,0.0f,forcedepth};
		BoxComp->AddImpulse(FORCE,NAME_None,true);*/
		JumpVelocity.Z = JumpHeight;
		bIsJumping = true;

		// Apply initial impulse
		FVector NewLocation = GetActorLocation() + FVector(0.0f, 0.0f, JumpHeight * 0.1f); // Small initial impulse
		SetActorLocation(NewLocation);

		// Start the gravity timer
		
		GetWorld()->GetTimerManager().SetTimer(JumpTimerHandle, this, &ARunningPlayer::ApplyGravity, 0.01f, true);

		
	}
	
	
}

void ARunningPlayer::ApplyGravity()
{
	if (bIsJumping)
	{

		// Update velocity with gravity
		JumpVelocity.Z += Gravity;

		// Move the pawn
		FVector NewLocation = GetActorLocation() + JumpVelocity * 0.01f;
		SetActorLocation(NewLocation);
		count++;

		FString D = FString::Printf(TEXT("%d"), count);
		UKismetSystemLibrary::PrintString(GetWorld(), D,true,true,FLinearColor::Black,5);

		// Check if the pawn has landed
		if (IsOnGround() && JumpVelocity.Z <= 0.0f)
		{
			StopJumping();
		}
	}
}

void ARunningPlayer::StopJumping()
{
	bIsJumping = false;
	JumpVelocity = FVector::ZeroVector;

	// Clear the gravity timer
	GetWorld()->GetTimerManager().ClearTimer(JumpTimerHandle);
}

bool ARunningPlayer::IsOnGround()
{
	FHitResult Hit;
	FVector Start = DirectionArrow->GetComponentLocation();
	FVector End = Start - FVector(0.0f, 0.0f, 50.0f);
	ECollisionChannel TraceChannel = ECC_Visibility;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool OnGround = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, TraceChannel, Params);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1, 0, 1);

	return OnGround;
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

