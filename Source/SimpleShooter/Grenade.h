// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
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
	void DebugComponentFinding();
	void DebugListOverLapActors();
public:	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* DamageSphere;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* HoldingComp;

	

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> OverlappingCharacters;

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

	UPROPERTY(EditAnywhere)
	USoundBase* ExplosionSound;
	UPROPERTY(EditAnywhere)
	USoundBase* ThrowSound;

	UPROPERTY(EditAnywhere)
	FVector EffectsScale = {10, 10, 10};
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void StartSimulate();
	void SimulatePath();
	void Explode();
	void DoDamage();
	UPROPERTY(EditDefaultsOnly)
	float SimulateRate = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float ExplosionCountTime = 5.f;

	float SimulateTimeRecord; //record the last time
	float ThrowTimeRecord;
};
