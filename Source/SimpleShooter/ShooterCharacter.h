// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h" 	
#include "Components/PawnNoiseEmitterComponent.h"
#include "ShooterCharacter.generated.h"

class AGun;
class UPawnSensingComponent;
UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
	float GetAmmo() const;

	UFUNCTION(BlueprintPure)
	FString Reloading() const;

	UFUNCTION(BlueprintPure)
	float GetTimer() const;

	
	UFUNCTION(BlueprintPure)
	float Healing();

	UPROPERTY(EditAnywhere)
	USoundBase* ReloadVoice;

	UPROPERTY(EditAnywhere)
	USoundBase* HealSound; 

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UPawnNoiseEmitterComponent* PawnNoiseEmitterComp;
	
	UFUNCTION()
	void OnHearNoise(APawn* NoiseInstigator, const FVector& Location, float Volume);
	FVector GunShotLocation;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	void shoot();
	void Reload();
	bool IsReloading = false;
	void ChangeToRifle();
	void ChangeToLauncher();
private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	APawn *PlayerPawn;
	UPROPERTY(EditAnywhere)
	float RotationRate = 10;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> RifleClass;//not the gun itself

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> LauncherClass;//not the gun itself


	UPROPERTY(EditDefaultsOnly)
	int CurrentGun = 1;//1 for Rifle 2 for Launcher
	
	UPROPERTY()
	AGun* Gun;

	UPROPERTY()
	AGun* Launcher;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;

	/* UPROPERTY(EditDefaultsOnly)
	ATriggerVolume* AmmoPlate;
 */
	FTimerHandle RestartTimer;

	UPROPERTY(EditDefaultsOnly)
	float HealingPercent = 0.1f;
	
};
