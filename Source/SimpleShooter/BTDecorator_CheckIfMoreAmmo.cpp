// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckIfMoreAmmo.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

UBTDecorator_CheckIfMoreAmmo::UBTDecorator_CheckIfMoreAmmo() 
{
    NodeName = "Check If any ammo left";   
}

void UBTDecorator_CheckIfMoreAmmo::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    //CalculateRawConditionValue
}

bool UBTDecorator_CheckIfMoreAmmo::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const 
{   
    Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
    if(OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("LeftAmmo")) < 1){
        return false;
    }
    else{
        return true;
    }
}
