// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"

#include "TankBarrel.h"
#include "TankTurret.h"

#include "TankAimingComponent.h" 

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{	
	if (!Barrel) { return; }

	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileSocket"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	//Calculates the OutLauchVelocity
	if (bHaveAimSolution)
	{
	auto AimDirection = OutLaunchVelocity.GetSafeNormal();

	FString OwningTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();

	/*UE_LOG(LogTemp, Warning, TEXT(
	"%s is aiming at : %s from : %s at %f at the direction of %s"), 
	*OwningTankName, *HitLocation.ToString(), *BarrelLocation, LaunchSpeed, *AimDirection.ToString()
	);*/
	
	MoveBarrelTowards(AimDirection);

	//Literally just gets time
	auto Time = GetWorld()->GetTimeSeconds();
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No AimSolution found"), Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Rotate turret, aiming barrel towards hitlocation
	auto CurrentTurretRotation = Turret->GetForwardVector().Rotation();
	auto CurrentAimRotation = AimDirection.Rotation();
	auto DeltaRotator = CurrentAimRotation - CurrentTurretRotation;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->RotateTurret(DeltaRotator.Yaw);
}

