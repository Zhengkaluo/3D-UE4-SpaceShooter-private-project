// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "HealingTriggerVolume.generated.h"
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AHealingTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsRefreshed = true;	
	virtual void Tick(float DeltaTime) override;

	void StartCountDown();
	float CurrentTime;
	float RecordTime;
public:
	

	// constructor sets default values for this actor's properties
	AHealingTriggerVolume();

	// overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// overlap end function
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	// specific actor for overlap
	/* 
 */
private:

	/* UPROPERTY(EditAnywhere)
	class AActor* Cube; */
};
