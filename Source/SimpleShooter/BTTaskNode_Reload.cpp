// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Reload.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTaskNode_Reload::UBTTaskNode_Reload() 
{
    NodeName = TEXT("Reload");
}
EBTNodeResult::Type UBTTaskNode_Reload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{   
    UE_LOG(LogTemp, Warning, TEXT("I Am AI Reload"));
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner() == nullptr){ 
        return EBTNodeResult::Failed;
    }
    
    AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner() -> GetPawn());
    
    if(Character == nullptr){
        return EBTNodeResult::Failed;
    }
    Character->Reload();


    return EBTNodeResult::Succeeded;
}


