// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetZeroAmmo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

UBTService_SetZeroAmmo::UBTService_SetZeroAmmo() 
{
    NodeName = TEXT("Set Zero Ammo value");
}

void UBTService_SetZeroAmmo::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), 0);
}
