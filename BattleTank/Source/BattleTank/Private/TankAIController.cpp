// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (!ControlledTank) { UE_LOG(LogTemp, Error, TEXT("TankAIController %s not found"), (*ControlledTank->GetName())) }
	else { UE_LOG(LogTemp, Warning, TEXT("TankAIController Pocessing %s"), (*ControlledTank->GetName())) }

	if (!PlayerTank) {UE_LOG(LogTemp, Error, TEXT("PlayerTank not found")) }
	else { UE_LOG(LogTemp, Warning, TEXT("Tank %s found PlayerTank %s"), (*ControlledTank->GetName()), (*PlayerTank->GetName())) }
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

	
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	return Cast<ATank>(PlayerPawn);
}
