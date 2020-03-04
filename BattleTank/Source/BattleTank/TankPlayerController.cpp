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
	//{	UE_LOG ( LogTemp, Warning, TEXT ("tankcontroller is ticking") ) }
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

	FVector OutHitLocation; //Out parameter
	if (GetSightRayHitLocation(OutHitLocation))// has "side-effect", will raytrace
	{
		// UE_LOG(LogTemp, Warning, TEXT("HitLocation: %S"), *OutHitLocation.ToString());
		// TODO Tell controlled tank to aim at this point
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// "De-project" the screen position of the crosshair to a world direction

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector out_WorldOrigin;
	FVector out_WorldDirection;

	void 	DeprojectScreenToWorld
	(
		const FVector2D & ScreenPos,
		const FIntRect & ViewRect,
		const FMatrix & InvViewMatrix,
		const FMatrix & InvProjMatrix,
		FVector & out_WorldOrigin,
		FVector & out_WorldDirection
	);

	UE_LOG(LogTemp, Warning, TEXT ("%s"), *out_WorldDirection.ToString())


	//UE_LOG(LogTemp, Warning, TEXT("Screenlocation = %s"), *ScreenLocation.ToString());
	
	// Line-trace along that look direction
	return true;
}

