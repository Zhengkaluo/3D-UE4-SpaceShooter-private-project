// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TriggerVolume.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "SimpleShooterGameModeBase.h"
// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnNoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitterComp"));
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{	
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	//PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Gun = GetWorld() -> SpawnActor<AGun>(RifleClass);
	Launcher = GetWorld() -> SpawnActor<AGun>(LauncherClass);
	//Launcher = GetWorld() -> SpawnActor<AGun>(LauncherClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
	
	if (PawnSensingComp)
	{
		//Registering the delegate which will fire when we hear something
		PawnSensingComp->OnHearNoise.AddDynamic(this, &AShooterCharacter::OnHearNoise);
	}
	
	//PawnSensingComp->OnSeePawn.AddDynamic(this, &AShooterCharacter::OnMySeePawn);
	//PawnSensor = FindComponentByClass<UPawnSensingComponent>();
	//PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(FName("Noise Sensor"));
	/* PawnSensor = PCIP.CreateDefaultSubobject<UPawnSensingComponent>(this, TEXT("Pawn Sensor"));
	PawnSensor->SensingInterval = .25f; // 4 times per second
	PawnSensor->bOnlySensePlayers = false;
	PawnSensor->SetPeripheralVisionAngle(85.f); */
	//NoiseSensingComponent
	/* Launcher = GetWorld() -> SpawnActor<AGun>(LauncherClass);
	GetMesh()->HideBoneByName(TEXT("backpack"), EPhysBodyOp::PBO_None);
	Launcher->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("BackpackWeapon"));
	Launcher->SetOwner(this); */
}

bool AShooterCharacter::IsDead() const
{
	if(CurrentHealth <= 0){
		return true;
	}
	else{
		return false;
	}
}

float AShooterCharacter::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

float AShooterCharacter::GetAmmo() const
{	if(CurrentGun == 1){
		return Gun -> ReturnAmmo();
	}
	else{
		return Launcher -> ReturnAmmo();
	}
	
}

FString AShooterCharacter::Reloading() const
{
	if(IsReloading == true){
		return TEXT("Relaoding...");
	}
	
	return TEXT("Good");
	
}

float AShooterCharacter::GetTimer() const
{
	return GetWorld()->GetTimeSeconds();
}

float AShooterCharacter::Healing() 
{
	float HealingValue = MaxHealth * HealingPercent;
	HealingValue = FMath::Min(MaxHealth - CurrentHealth, HealingValue);
	CurrentHealth += HealingValue;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HealSound, GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Character currentHealth %f value"), CurrentHealth);
	return HealingValue;
}

void AShooterCharacter::OnHearNoise(APawn* NoiseInstigator, const FVector& Location, float Volume) 
{
	//Super::OnHeardNoise(NoiseInstigator, Location, Volume);
	GunShotLocation = Location;
	UE_LOG(LogTemp, Warning, TEXT("I am %s, I Hear %s fired noise at location: %s"), *(GetName()),  *(NoiseInstigator->GetName()), *(Location.ToString()));
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::shoot);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Reload);
	PlayerInputComponent->BindAction(TEXT("ChangeToRifle"), EInputEvent::IE_Pressed, this, &AShooterCharacter::ChangeToRifle);
	PlayerInputComponent->BindAction(TEXT("ChangeToLauncher"), EInputEvent::IE_Pressed, this, &AShooterCharacter::ChangeToLauncher);
	//PlayerInputComponent->BindAction(TEXT("Heal"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Healing);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(CurrentHealth, DamageApplied);
	CurrentHealth -= DamageApplied;
	UE_LOG(LogTemp, Warning, TEXT("current Health %f"), CurrentHealth);

	if(IsDead()){
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if(GameMode != nullptr){
			GameMode -> PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		//switch of capsule component
		GetCapsuleComponent() -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageApplied;
}

void AShooterCharacter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue) 
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue) 
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::shoot() 
{	
	
	if(IsReloading == false){
		//MakeNoise if really shooting
		AActor::MakeNoise(0.4, this, GetActorLocation());
		if(CurrentGun == 1){
			Gun->PullTrigger();
		}
		else{
			Launcher->PullTrigger();
		}
	}
	
	
}

void AShooterCharacter::Reload() 
{
	if(IsReloading == false){
		IsReloading = true;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadVoice, GetActorLocation());
		if(CurrentGun == 1){
			
			UE_LOG(LogTemp, Warning, TEXT("Reloading"));
			GetWorldTimerManager().SetTimer(RestartTimer, Gun, &AGun::Reload, 3);
		}
		else{
			GetWorldTimerManager().SetTimer(RestartTimer, Launcher, &AGun::Reload, 6);
		}
	}
	
	
}

void AShooterCharacter::ChangeToRifle() 
{
	//Gun = GetWorld() -> SpawnActor<AGun>(RifleClass);
	//GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	CurrentGun = 1;
	Launcher -> DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
	UE_LOG(LogTemp, Warning, TEXT("Change To Rifle"));
}

void AShooterCharacter::ChangeToLauncher() 
{
	//Gun = GetWorld() -> SpawnActor<AGun>(LauncherClass);
	//GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	CurrentGun = 2;
	Gun -> DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	Launcher->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Launcher->SetOwner(this);
	UE_LOG(LogTemp, Warning, TEXT("Change To Laucher"));
}
