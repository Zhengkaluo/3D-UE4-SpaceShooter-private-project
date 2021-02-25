// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Grenade.generated.h"
class AShooterCharacter;

UCLASS()
class SIMPLESHOOTER_API AGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector Accesend = {0, 0, 100};
	FVector Deccesend = {0, 0, -100};
private:
	FVector PlayerLocation = {0, 0, 0};
 	FRotator PlayerRotator = {0, 0, 0};

	AShooterCharacter* PlayerShooter;

public:	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;



	UPROPERTY(VisibleAnywhere)
	USceneComponent* HoldingComp;

	void Throw();
	UCameraComponent* PlayerCamera;
	FVector ForwardVector;

	UPROPERTY(VisibleAnywhere)
	bool IsHolding;//if player holding the grenade
	UPROPERTY(VisibleAnywhere)
	bool IsGravity;
	UPROPERTY(VisibleAnywhere)
	bool IsSimulating = false;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ExplodeFlash;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void StartSimulate();
	void SimulatePath();
	void Explode();

	UPROPERTY(EditDefaultsOnly)
	float SimulateRate = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float ExplosionCountTime = 5.f;

	float SimulateTimeRecord; //record the last time
	float ThrowTimeRecord;
};
