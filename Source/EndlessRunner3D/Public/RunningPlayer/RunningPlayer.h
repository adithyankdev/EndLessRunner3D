// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "RunningPlayer.generated.h"

//class UArrowComponent;
class AbstractClass;
class SideMoveConcrete;
class JumpConcrete;

UCLASS()
class ENDLESSRUNNER3D_API ARunningPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARunningPlayer();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player Base")
	UBoxComponent* BoxComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	UArrowComponent* DirectionArrow;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AbstractClass* CurrentState;
	SideMoveConcrete* SideMovetState;
	JumpConcrete* JumpState;
	

public:	
	virtual void Tick(float DeltaTime) override;

	
	float LatestSideWayDirection;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	class UFloatingPawnMovement* Movement;

	bool isjump;

	UFUNCTION()
	void MoveAction(const struct FInputActionValue& InputValue);
	UFUNCTION()
	void JumpAction(const struct FInputActionValue& InputValue);

	UPROPERTY(EditAnywhere)
	float JumpHeight;

	UPROPERTY(EditAnywhere)
	float Gravity;

	FVector JumpVelocity;
	bool bIsJumping;

	FTimerHandle JumpTimerHandle;

	void ApplyGravity();
	void StopJumping();
	bool IsOnGround();
	float speed;

	//Checking How many times the apply grvity call -> around 98 times 
	int count;

	

};
