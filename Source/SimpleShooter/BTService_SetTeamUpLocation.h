// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetTeamUpLocation.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTService_SetTeamUpLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_SetTeamUpLocation();

	UPROPERTY(EditDefaultsOnly)
	FVector TeamUpPlace = {2284.726807, -3401.155762, 72.476135};
	
	UPROPERTY(EditDefaultsOnly)
	FVector AnotherTeamUpPlace = {2374.726807, -6891.155762, 72.476135};
	
	UPROPERTY(EditDefaultsOnly)
	FVector LastTeamUpPlace = {3970.000000, -6340.000000, 40.000000};

	//FVector LastTeamUpPlace = {2260.000000, -10290.000000, 40.000000};
	FVector LocationArray[3] = {TeamUpPlace, AnotherTeamUpPlace, LastTeamUpPlace};
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;	
};
