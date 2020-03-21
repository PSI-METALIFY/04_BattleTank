// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declaretion
class UTankBarrel; 
class UTankTurret;

// Holds barrel properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	void SetTurretReference(UTankTurret* TurretToSet);

	// TODO add SetTurretReference

	void AimAt(FVector HitLocation, float LaunchSpeed);

protected:

private:	


	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;
	
	void MoveBarrelTowards(FVector AimDirection);

	void MoveTurretTowards(FVector AimDirection);
};
