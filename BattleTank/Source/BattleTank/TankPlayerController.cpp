// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) { UE_LOG( LogTemp, Error, TEXT("TankPlayerController %s not found"), ( *ControlledTank->GetName() ) ) }
	else { UE_LOG( LogTemp, Warning, TEXT("TankPlayerController Pocessing %s"), ( *ControlledTank->GetName() ) ) }
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
