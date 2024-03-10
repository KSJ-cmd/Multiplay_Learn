// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (HasAuthority()) {


		auto location = GetActorLocation();
		auto Dir = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		float Length = (GlobalTargetLocation - GlobalStartLocation).Size();
		float Travelled = (location - GlobalStartLocation).Size();
		if(Length <= Travelled)
		{
			Swap(GlobalStartLocation, GlobalTargetLocation);
		}
		
		location += Dir * MovingSpeed * DeltaSeconds;
		SetActorLocation(location);
	}
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}
