// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay() 
{
    Super::BeginPlay();

    //set focus
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    //virtual void SetFocus(AActor* NewFocus, EAIFocusPriority::Type InPriority = EAIFocusPriority::Gameplay);
    if(AIBehavior != nullptr){
        RunBehaviorTree(AIBehavior);
        //GetBlackboardComponent() -> SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn -> GetActorLocation());
        if(GetPawn() != nullptr){
            GetBlackboardComponent() -> SetValueAsVector(TEXT("StartLocation"), GetPawn() -> GetActorLocation());
        }
        else{
            GetBlackboardComponent() -> SetValueAsVector(TEXT("StartLocation"), FVector(2374.000732, -6891.999023, 72.000000));//(X=2374.726807,Y=-6891.155762,Z=72.476135)
        }
    }
}

void AShooterAIController::Tick(float DeltaSeconds) 
{
    Super::Tick(DeltaSeconds);
    /* APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    //MoveToActor(PlayerPawn, 200);

    //If Line Of Sight
        //MoveTo
        //SetFocus
    //Else
        //ClearFocus
        //StopMovement
    //virtual bool LineOfSightTo(const AActor* Other, FVector ViewPoint = FVector(ForceInit), bool bAlternateChecks = false) const override;
    if(LineOfSightTo(PlayerPawn)){
        //setting player location
        //set last known location
        GetBlackboardComponent() -> SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn -> GetActorLocation());
        GetBlackboardComponent() -> SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn -> GetActorLocation());
    }
    
    else{
        GetBlackboardComponent() -> ClearValue(TEXT("PlayerLocation"));
    }  */
//    RunBehaviorTree(Beha)
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
    if(ControlledCharacter != nullptr){
        return ControlledCharacter->IsDead();
    }
    return true;
}
