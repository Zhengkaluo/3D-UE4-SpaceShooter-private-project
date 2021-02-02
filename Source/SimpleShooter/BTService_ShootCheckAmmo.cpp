// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ShootCheckAmmo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTService_ShootCheckAmmo::UBTService_ShootCheckAmmo() 
{
    NodeName = TEXT("Update LeftAmmo for Shooting");
}

void UBTService_ShootCheckAmmo::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

     if(OwnerComp.GetAIOwner() == nullptr){ 
        return;
    }
    
    AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner() -> GetPawn());
    if(Character == nullptr){
        return;
    }
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), Character -> GetAmmo());
}
