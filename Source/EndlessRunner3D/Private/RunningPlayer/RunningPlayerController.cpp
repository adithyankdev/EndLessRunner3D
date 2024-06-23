// Fill out your copyright notice in the Description page of Project Settings.


#include "RunningPlayer/RunningPlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void ARunningPlayerController::SetupInputComponent()
{
    FString D = TEXT("Controller Begin SetPlayerInputComponent");
    UKismetSystemLibrary::PrintString(GetWorld(), D, true, true, FLinearColor::Yellow);


    PlayerMappingContext = NewObject<UInputMappingContext>(this);
    MoveInput = NewObject<UInputAction>(this);

    MoveInput->ValueType = EInputActionValueType::Axis1D;
    PlayerMappingContext->MapKey(MoveInput, EKeys::Right);
    FEnhancedActionKeyMapping& Mapping = PlayerMappingContext->MapKey(MoveInput, EKeys::Left);
    UInputModifierNegate* Negate = NewObject<UInputModifierNegate>(this);
    Mapping.Modifiers.Add(Negate);

 
    
 
    UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent);


   /*  check(PlayerCharacter)
     {
         EnhancedInputComp->BindAction(MoveInput, ETriggerEvent::Started,PlayerCharacter, &ARunningPlayer::MoveAction);

         ULocalPlayer* LocalPlayer = GetLocalPlayer();
        check(LocalPlayer)
         {
             UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

            check(Subsystem)
             {
                 Subsystem->ClearAllMappings();
                 Subsystem->AddMappingContext(PlayerMappingContext, 0);
             }
         }
     }*/
}

void ARunningPlayerController::BeginPlay()
{
    FString D = TEXT("Controller Begin Play");
    UKismetSystemLibrary::PrintString(GetWorld(), D, true, true, FLinearColor::Yellow);

    PlayerCharacter = Cast<ARunningPlayer>(GetPawn());
    if (PlayerCharacter)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerCharacter is good"));
   }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerCharacter is NULL "));
    }
    

}
