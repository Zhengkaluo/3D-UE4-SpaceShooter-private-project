// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetTeamUpLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTService_SetTeamUpLocation::UBTService_SetTeamUpLocation() 
{
    NodeName = TEXT("Set TeamUp Location");
}

void UBTService_SetTeamUpLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

     if(OwnerComp.GetAIOwner() == nullptr){ 
        return;
    }
    AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner() -> GetPawn());
    if(Character == nullptr){
        return;
    }
    /* if(Character->TeamUpPlace == nullptr){
        return;
    } */
    int LocationIndex = rand() % 3;
    FVector Location = LocationArray[LocationIndex];
     OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location);
}
