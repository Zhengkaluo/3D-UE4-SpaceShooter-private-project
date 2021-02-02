// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    Crosshairs->RemoveFromViewport();
    if(bIsWinner){
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if(WinScreen != nullptr){
            WinScreen -> AddToViewport();
        }
    }
    else{
        UE_LOG(LogTemp, Warning, TEXT("We have finished"));


        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if(LoseScreen != nullptr){
            LoseScreen -> AddToViewport();
        }
    }
    

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

    
}

/* AShooterPlayerController* AShooterPlayerController::ReturnPlayerController() 
{
    return this;
}   */

void AShooterPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    
    Crosshairs = CreateWidget(this, CrosshairsClass);
    if(Crosshairs != nullptr){
        Crosshairs -> AddToViewport();
    } 
}
