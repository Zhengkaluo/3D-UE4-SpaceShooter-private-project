// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include <iostream>
#include <fstream>
#include "GameFramework/Controller.h"
#include "ShooterCharacter.h"
#include "ShooterAIController.h"
using namespace std;
void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled) 
{
    Super::PawnKilled(PawnKilled);
    //UE_LOG(LogTemp, Warning, TEXT("A Pawn Was killed"));
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled -> GetController());
    if(PlayerController != nullptr){
       EndGame(false);
    }
    for(AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld())){
        if(!Controller -> IsDead()){
            return;
        }
    }
    GameTime = GetWorld() -> GetTimeSeconds();
    RecordTimeToDatatable();
    EndGame(true);
    //for loop over shooterAi in world
        //is not dead?
            //return exit
    //all dead?
        //return endgame true
    
}

float AKillEmAllGameMode::GetTimer() const
{
    return GameTime;
}

float AKillEmAllGameMode::GetCurrentTime() const
{
    return GetWorld() -> GetTimeSeconds();
}

void AKillEmAllGameMode::Tick(float DeltaTime) 
{   
    Super::Tick(DeltaTime);
    if(GetCurrentTime() - LastSpawnTime >= 7.0f){
        if(CurrentSpawning <= 16){
            SpawnEnemy();
            LastSpawnTime = GetCurrentTime();
        }
    }
    
    
}

void AKillEmAllGameMode::BeginPlay() 
{   
    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.bCanEverTick = true;
    if(DataTable == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("Datable Not Found!"));
    }
    //SpawnEnemy();
    //SpawnEnemy();
    //SpawnEnemy();
    //SpawnEnemy();
    /*if(!SpawnLocation){
            UE_LOG(LogTemp, Warning, TEXT("No location found"));
    }*/    
    //AIEnemy = GetWorld() -> SpawnActor<AShooterCharacter>(ShooterAIClass, SpawnVector, SpawnRotation);
    //AIEnemy -> SetActorLocationAndRotation(SpawnLocation -> GetActorLocation(), SpawnLocation -> GetActorRotation(), false, 0, ETeleportType::None);

} 

void AKillEmAllGameMode::SpawnEnemy() 
{   
    int index;
    //for(;CurrentSpawning < 1; CurrentSpawning++){
    index = rand() % 3;
    FVector ChosenVector = SpawnLocationArray[index];
    UE_LOG(LogTemp, Warning, TEXT("SPawnLocation %s Rotation %s"), *(ChosenVector.ToString()), *(SpawnRotation.ToString()));
    // AIEnemy = GetWorld() -> SpawnActor<AShooterCharacter>(ShooterAIClass);
    if(CurrentSpawning < 8){
        AIEnemy[CurrentSpawning] = GetWorld() -> SpawnActor<AShooterCharacter>(ShooterAIClass, ChosenVector, SpawnRotation);
    }
    else{
        AIEnemy[CurrentSpawning] = GetWorld() -> SpawnActor<AShooterCharacter>(ShooterStrongAIClass, ChosenVector, SpawnRotation);
    }
    CurrentSpawning++;
    //}
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner) 
{   
    for (AController* Controller : TActorRange<AController>(GetWorld()))  {
        bool bIsWinner = Controller -> IsPlayerController() == bIsPlayerWinner;
        Controller -> GameHasEnded(Controller -> GetPawn(), bIsWinner);
    }
    
}

void AKillEmAllGameMode::RecordTimeToDatatable() 
{
    if(DataTable == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("Datable Not Found!"));
    }
    else{
        //RowData.
       // DataTable->AddRow(TEXT("RowNameNew"), *RowData);
    }
}
