// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayGameInstance.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"
UMultiplayGameInstance::UMultiplayGameInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if(MainMenuBPClass.Class!=nullptr)
	{
		MainMenuClass = MainMenuBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (MainMenuBPClass.Class != nullptr)
	{
		InGameMenuClass = InGameMenuBPClass.Class;
	}



	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
}

void UMultiplayGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
	UE_LOG(LogTemp, Warning, TEXT("MainMenu class : %s"),*MainMenuClass->GetName());
	UE_LOG(LogTemp, Warning, TEXT("MainMenu class : %s"), *InGameMenuClass->GetName());

}

void UMultiplayGameInstance::LoadMenu()
{
	if (MainMenuClass!= nullptr) {
		Main = CreateWidget<UMainMenu>(this, MainMenuClass);
		if (Main != nullptr) {
			Main->Setup();
			Main->SetMenuInterface(this);
		}
	}
	
}

void UMultiplayGameInstance::LoadInGameMenu()
{
	if (InGameMenuClass != nullptr) {
		InGame = CreateWidget<UInGameMenu>(this, InGameMenuClass);
		if (InGame != nullptr) {
			InGame->Setup();
			InGame->SetMenuInterface(this);
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
	if(Main!=nullptr)
	{
		Main->Teardown();
	}
	auto world = GetWorld();
	if(world)
	{
		world->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
	}
}

void UMultiplayGameInstance::Join(const FString& Address)
{
	if (Main != nullptr)
	{
		Main->Teardown();
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Join %s"), *Address));;
	}
	auto pc = GetFirstLocalPlayerController(GetWorld());
	if (pc) {
		pc->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}
