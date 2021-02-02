// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_HearNoise.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTService_HearNoise::UBTService_HearNoise() 
{
    NodeName = TEXT("Check If Hear Noise");

}

void UBTService_HearNoise::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
     Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if(OwnerComp.GetAIOwner() == nullptr){ 
        return;
    }
    
    AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner() -> GetPawn());
    
    if(Character == nullptr){
        return;
    }
    
    OwnerComp.GetBlackboardComponent() -> SetValueAsVector(GetSelectedBlackboardKey() , Character -> GunShotLocation);

   /* if(Character -> GunShotLocation != (0.0, 0.0, 0.0)){
    }
    else{
       OwnerComp.GetBlackboardComponent() ->ClearValue(GetSelectedBlackboardKey());
    } */
    
}



