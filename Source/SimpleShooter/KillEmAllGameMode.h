// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "Engine/DataTable.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillEmAllGameMode : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()
public:
	virtual void PawnKilled(APawn* PawnKilled) override;
	
	UFUNCTION(BlueprintPure)
	float GetTimer() const;
	
	float GameTime;

	UFUNCTION(BlueprintPure)
	float GetCurrentTime() const;

	float LastSpawnTime = 0.f;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	FVector SpawnLocation = {2560.726807, -3850.155762, 70.476135};
	
	UPROPERTY(EditDefaultsOnly)
	FVector SpawnLocation2 = {7460.726807, -5710.155762, 551.476135};
	//(X=7460.000000,Y=-5710.000000,Z=470.000000)
	UPROPERTY(EditDefaultsOnly)
	FVector SpawnLocation3 = {1740.000000, -5160.000000, 1110.000000};
	//(X=1740.000000,Y=-5160.000000,Z=1110.000000)
	FRotator SpawnRotation = FRotator( 2.000000, 2.000000, 1.000000);
	FVector SpawnLocationArray[3] = {SpawnLocation, SpawnLocation2, SpawnLocation3};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnEnemy();

	//UPROPERTY(BlueprintReadOnly)
	bool PlayerDead;
private:
	void EndGame(bool bIsPlayerWinner);

	UPROPERTY(EditDefaultsOnly)
	UDataTable* DataTable;
	
	//UPROPERTY(EditDefaultsOnly)
	//FTableRowBase* RowData;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AShooterCharacter> ShooterAIClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AShooterCharacter> ShooterStrongAIClass;

	UPROPERTY()
	AShooterCharacter* AIEnemy[18];

	UPROPERTY(EditDefaultsOnly)
	int CurrentSpawning = 0;

	
	/* UPROPERTY()
	FActorSpawnParameters* SpawnParameters; */
    

	void RecordTimeToDatatable();
};
