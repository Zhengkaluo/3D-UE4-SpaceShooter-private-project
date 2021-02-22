// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "Grenade.h"

// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrenade::SimulatePath(AController* OwnerController, const FVector& PlayerLocation, const FRotator& PlayerRotator) 
{
	//void DrawDebugDirectionalArrow(const UWorld* InWorld, FVector const& LineStart, FVector const& LineEnd, float ArrowSize, FColor const& Color, bool bPersistentLines = false, float LifeTime=-1.f, uint8 DepthPriority = 0, float Thickness = 0.f);
	//OwnerController->GetPlayerViewPoint(PlayerLocation, PlayerRotator);
	//ShotDirection = -PlayerLocation.Vector();
	FVector End = PlayerLocation + PlayerRotator.Vector() * 10;
	DrawDebugDirectionalArrow(GetWorld(), PlayerLocation, End, 5.f, FColor::Orange, false, 10.f, 0, 5.f);
}

