// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::RotateTurret(float MaxRotateSpeed)
{
	MaxRotateSpeed = (50 * GetWorld()->DeltaTimeSeconds) + RelativeRotation.Yaw;

	SetRelativeRotation(FRotator(0, MaxRotateSpeed, 0));
}