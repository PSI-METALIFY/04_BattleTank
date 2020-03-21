// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "Tank.h"

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

	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation))// has "side-effect", will raytrace
	{		
		
		GetControlledTank()->AimAt(HitLocation);
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// "De-project" the screen position of the crosshair to a world direction

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector LookDirection;

	if (GetlookDirection(ScreenLocation, LookDirection))
	{
	// Line-trace along that look direction
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *LookDirection.ToString())
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Screenlocation = %s"), *ScreenLocation.ToString());
	
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto LineTrace_StartLocation = PlayerCameraManager->GetCameraLocation();
	auto LineTrace_EndLocation = LineTrace_StartLocation + (LookDirection * LineTrace_Range);

	if (GetWorld()->LineTraceSingleByChannel
			(
				HitResult,
				LineTrace_StartLocation,
				LineTrace_EndLocation,
				ECollisionChannel::ECC_Visibility
			)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetlookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;// is discarded

	return DeprojectScreenPositionToWorld
	(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}


