// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayGameInstance.h"
#include "Engine/Engine.h"
UMultiplayGameInstance::UMultiplayGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
}

void UMultiplayGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

void UMultiplayGameInstance::Host()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Exec Host"));
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Host"));
	}

	auto world = GetWorld();
	if(world)
	{
		world->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
	}
}

void UMultiplayGameInstance::Join(const FString& Address)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Join %s"), *Address));;
	}
}
