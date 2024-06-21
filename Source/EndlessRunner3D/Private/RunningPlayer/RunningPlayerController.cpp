// Fill out your copyright notice in the Description page of Project Settings.


#include "RunningPlayer/RunningPlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "RunningPlayer/RunningPlayer.h"

void ARunningPlayerController::SetupInputComponent()
{
    PlayerMappingContext = NewObject<UInputMappingContext>(this);
    MoveInput = NewObject<UInputAction>(this);

    MoveInput->ValueType = EInputActionValueType::Axis1D;
    PlayerMappingContext->MapKey(MoveInput, EKeys::Right);
    FEnhancedActionKeyMapping& Mapping = PlayerMappingContext->MapKey(MoveInput, EKeys::Left);
    UInputModifierNegate* Negate = NewObject<UInputModifierNegate>(this);
    Mapping.Modifiers.Add(Negate);

    APawn* Pawnn = GetPawn();
    ARunningPlayer* PlayerCharacter = Cast<ARunningPlayer>(Pawnn);
    if (!PlayerCharacter)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerCharacter is nullptr"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerCharacter good"));
    }
    /*UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent);



     if (!EnhancedInputComp)
     {

     }
     if (!PlayerCharacter)
     {
         UE_LOG(LogTemp, Error, TEXT("PlayerCharacter is nullptr"));
     }

     if(EnhancedInputComp && PlayerCharacter)
     {
         EnhancedInputComp->BindAction(MoveInput, ETriggerEvent::Started, PlayerCharacter, &ARunningPlayer::MoveAction);

         ULocalPlayer* LocalPlayer = GetLocalPlayer();
        if(LocalPlayer)
         {
             UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

            if(Subsystem)
             {
                 Subsystem->ClearAllMappings();
                 Subsystem->AddMappingContext(PlayerMappingContext, 0);
             }
         }
     }*/
}
