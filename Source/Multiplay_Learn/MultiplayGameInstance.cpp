// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayGameInstance.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

const static  FName SESSION_NAME = TEXT("My Session Game");

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
	OnlineSubsystem = IOnlineSubsystem::Get();
	if(OnlineSubsystem!=nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystem class : %s"), *OnlineSubsystem->GetSubsystemName().ToString());
		UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystem class : %s"), *OnlineSubsystem->GetOnlineServiceName().ToString());
		const IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{

			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMultiplayGameInstance::OnDestroySessionComplete);
		}

	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystem no class "));
	}
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));

}

void UMultiplayGameInstance::LoadMenuWidget()
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
	const IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
	if (SessionInterface.IsValid())
	{
		auto namedSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (namedSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
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

void UMultiplayGameInstance::LoadMainMenu()
{
	auto pc = GetFirstLocalPlayerController(GetWorld());
	if (pc) {
		pc->ClientTravel("/Game/Multiplay_Learn/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
	}
}

void UMultiplayGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if(!Success)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Exec Host"));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Host"));
	}
	if (Main != nullptr)
	{
		Main->Teardown();
	}
	auto world = GetWorld();
	if (world)
	{
		world->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
	}
}

void UMultiplayGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if(Success)
	{
		CreateSession();
	}
}

void UMultiplayGameInstance::CreateSession()
{
	const IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
	if (SessionInterface.IsValid()) {
		FOnlineSessionSettings SessionSettings;
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}
