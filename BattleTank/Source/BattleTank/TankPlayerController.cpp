// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) { UE_LOG( LogTemp, Error, TEXT("TankPlayerController %s not found"), ( *ControlledTank->GetName() ) ) }
	else { UE_LOG( LogTemp, Warning, TEXT("TankPlayerController Pocessing %s"), ( *ControlledTank->GetName() ) ) }
}

//tick
void ATankPlayerController::Tick(float DeltaTime)
{
//super
	Super::Tick(DeltaTime);
	{	UE_LOG ( LogTemp, Warning, TEXT ("tankcontroller is ticking") ) }
	//aim towards reticle
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	//get world location if linetrace through crosshair
	// if it hits the landscape
		// tell controlled tank to aim at this point
}