// Fill out your copyright notice in the Description page of Project Settings.
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))


#include "HealingTriggerVolume.h"
// include draw debug helpers header file
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

AHealingTriggerVolume::AHealingTriggerVolume() 
{
    PrimaryActorTick.bCanEverTick = true;
      //Register Events
    OnActorBeginOverlap.AddDynamic(this, &AHealingTriggerVolume::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &AHealingTriggerVolume::OnOverlapEnd);
}

void AHealingTriggerVolume::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor) 
{
    UE_LOG(LogTemp, Warning, TEXT("Overlap Begin Overlapping Actor = %s"), *OtherActor->GetName());
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    AShooterCharacter* OwnerCharacter = Cast<AShooterCharacter>(PlayerPawn); 
    //if the overlapping actor is the specific actor we identified in the editor
    if (OtherActor && (OtherActor != this))
    {
        //UE_LOG(LogTemp, Warning, TEXT("Overlap Begin Overlapping Actor = %s"), *OtherActor->GetName());
        if(OtherActor->GetName() == "BP_PlayerShooterCharacter_C_0"){
            UE_LOG(LogTemp, Warning, TEXT("This is player actor"));
            if(OwnerCharacter -> GetHealthPercent() != 1 && IsRefreshed == true){//else no need for healing
                OwnerCharacter -> Healing();
                IsRefreshed = false;
                StartCountDown(); 
            }
        }
    }
}

void AHealingTriggerVolume::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor) 
{
    //IsRefreshed = false;
}

void AHealingTriggerVolume::BeginPlay() 
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("I am heal trigger"));
    //SpecificActor = GetWorld()
    //void DrawDebugBox(const UWorld* InWorld, FVector const& Center, FVector const& Box, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    //void DrawDebugString(const UWorld* InWorld, FVector const& TextLocation, const FString& Text, class AActor* TestBaseActor, FColor const& TextColor, float Duration, bool bDrawShadow, float FontScale)
	
	//DrawDebugString(GetWorld(), GetActorLocation(), TEXT("Healing Box"), this, FColor::Turquoise, -1, 1, 5);
    //Cube -> SetOwner(this);
    DrawDebugBox(GetWorld(), GetActorLocation(), GetActorScale()*100, FColor::Turquoise, true, -1, 0, 5);
}    

void AHealingTriggerVolume::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    CurrentTime = GetWorld()->GetTimeSeconds();
    if(CurrentTime - RecordTime >= 10.f && IsRefreshed == false){
        UE_LOG(LogTemp, Warning, TEXT("Healing Refresh"));
        IsRefreshed = true;
        //DrawDebugBox(GetWorld(), GetActorLocation(), GetActorScale()*100, FColor::Turquoise, true, -1, 0, 5);
    }
    /* else{
        //DrawDebugBox(GetWorld(), GetActorLocation(), GetActorScale()*100, FColor::Red, true, -1, 0, 5);
    } */
    
}

void AHealingTriggerVolume::StartCountDown() 
{
    RecordTime = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("Start Count down, RecordTime %f"), RecordTime);
    DrawDebugBox(GetWorld(), GetActorLocation(), GetActorScale()*101, FColor::Red, false, 10.f, 0, 5);
    //Cube -> DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
    //timer
}


