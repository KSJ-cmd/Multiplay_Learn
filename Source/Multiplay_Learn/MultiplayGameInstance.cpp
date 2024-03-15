// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayGameInstance.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "MenuSystem/MainMenu.h"
UMultiplayGameInstance::UMultiplayGameInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if(MainMenuBPClass.Class!=nullptr)
	{
		MainMenuClass = MainMenuBPClass.Class;
	}


	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
}

void UMultiplayGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
	UE_LOG(LogTemp, Warning, TEXT("MainMenu class : %s"),*MainMenuClass->GetName());
}

void UMultiplayGameInstance::LoadMenu()
{
	if (MainMenuClass!= nullptr) {
		Menu = CreateWidget<UMainMenu>(this, MainMenuClass);
		if (Menu != nullptr) {
			Menu->Setup();
			Menu->SetMenuInterface(this);
		}
	}
	
}

void UMultiplayGameInstance::Host()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Exec Host"));
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Host"));
	}
	if(Menu!=nullptr)
	{
		Menu->Teardown();
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
	auto pc = GetFirstLocalPlayerController(GetWorld());
	if (pc) {
		pc->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}
