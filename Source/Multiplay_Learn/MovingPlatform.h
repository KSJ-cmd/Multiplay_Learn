// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAY_LEARN_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AMovingPlatform();

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = Speed)
	float MovingSpeed = 0;
	UPROPERTY(EditAnywhere,meta=(MakeEditWidget=true))
	FVector TargetLocation;

private:
	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;
};
