// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "Grenade.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "ShooterCharacter.h"
// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Mesh->SetupAttachment(Root);

	Mesh -> SetSimulatePhysics(true);

	IsHolding = false;
	IsGravity = false;
}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();
	PlayerShooter = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if(PlayerShooter != nullptr){
		PlayerCamera = PlayerShooter->FindComponentByClass<UCameraComponent>();
	}
	/* if(PlayerCamera != nullptr){
		UE_LOG(LogTemp, Warning, TEXT("%s Camera found"), *GetName());
	} */

	TArray<USceneComponent*> Components;
	PlayerShooter -> GetComponents(Components);
	 if(Components.Num() > 0){
		for(auto& Comp : Components){
			if(Comp -> GetName() == "HoldingComponent")
			{
				HoldingComp = Cast<USceneComponent>(Comp);
			}
		}
	} 
	UE_LOG(LogTemp, Warning, TEXT("Holding Component name %s"), *HoldingComp -> GetName())

	//
}

void AGrenade::Throw() 
{
	IsHolding = false;
	Mesh -> SetSimulatePhysics(IsHolding ? false : true);
	Mesh -> SetCollisionEnabled(IsHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);
	ForwardVector = PlayerCamera->GetForwardVector();
	Mesh -> AddForce (((ForwardVector * 100000) + Accesend * 600) * Mesh -> GetMass());

	//Start explode countdown
	ThrowTimeRecord = GetWorld() -> GetTimeSeconds();
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float CurrentTime = GetWorld() -> GetTimeSeconds();
	if(IsHolding && HoldingComp){
		//void SetRelativeLocation(FVector NewLocation, bool bSweep=false, FHitResult* OutSweepHitResult=nullptr, ETeleportType Teleport = ETeleportType::None);
		//Root -> SetRelativeLocation(HoldingComp -> GetComponentLocation());
		SetActorLocationAndRotation(HoldingComp -> GetComponentLocation() ,HoldingComp -> GetComponentRotation());
		Mesh -> SetRelativeTransform(GetActorTransform());
		if(CurrentTime - SimulateTimeRecord >= 1/SimulateTimeRecord){		
			SimulatePath();
		}
	}
	//FTransform MeshTransform = Mesh -> GetRelative();
	else{
		SetActorTransform(Mesh -> GetRelativeTransform());
	} 
	if(IsHolding == false && CurrentTime - ThrowTimeRecord >ExplosionCountTime){
		UE_LOG(LogTemp, Warning, TEXT("Calling explode function"));
		Explode();
	}
	
}

void AGrenade::StartSimulate() 
{
	IsSimulating = true;
	IsHolding = true;
	IsGravity = !IsGravity;
	Mesh -> SetEnableGravity(IsGravity);
	Mesh -> SetSimulatePhysics(IsHolding ? false : true);
	Mesh -> SetCollisionEnabled(IsHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);
	SimulateTimeRecord = GetWorld()->GetTimeSeconds();
	//void DrawDebugDirectionalArrow(const UWorld* InWorld, FVector const& LineStart, FVector const& LineEnd, float ArrowSize, FColor const& Color, bool bPersistentLines = false, float LifeTime=-1.f, uint8 DepthPriority = 0, float Thickness = 0.f);
	//OwnerController->GetPlayerViewPoint(PlayerLocation, PlayerRotator);
	UE_LOG(LogTemp, Warning, TEXT("On Throw Press, simulating path"));
	SimulatePath();
}

void AGrenade::SimulatePath() 
{
	//PlayerShooter = Cast<AShooterCharacter>(GetOwner());
	//PlayerLocation = PlayerShooter->GetActorLocation();
	PlayerLocation = HoldingComp -> GetComponentLocation();
	PlayerRotator = PlayerShooter->GetActorRotation();
	FVector FirstEnd = PlayerLocation + (PlayerCamera->GetForwardVector() * 500.f + Accesend);
	FVector SecondEnd = FirstEnd + (PlayerCamera->GetForwardVector() * 500.f + Deccesend);
	DrawDebugDirectionalArrow(GetWorld(), PlayerLocation, FirstEnd, 10.f, FColor::Red, false, 0.05f, 0, 2.5f); 
	DrawDebugDirectionalArrow(GetWorld(), FirstEnd, SecondEnd, 10.f, FColor::Blue, false, 0.05f, 0, 2.5);
}

void AGrenade::Explode() 
{	
	if(ExplodeFlash != nullptr){
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeFlash, GetActorLocation(), GetActorRotation());
	}
	ThrowTimeRecord = 0.f;
	//UE_LOG(LogTemp, Warning, TEXT("My transform to root %s"), *(Mesh -> TransformToRoot)->ToString());
	UE_LOG(LogTemp, Warning, TEXT("%s exploded"), *GetName());
	this -> Destroy();
}

