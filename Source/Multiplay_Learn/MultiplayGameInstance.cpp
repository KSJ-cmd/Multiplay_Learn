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
#include "Online/OnlineSessionNames.h"

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
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiplayGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMultiplayGameInstance::OnJoinSessionComplete);
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

void UMultiplayGameInstance::Join(uint32 Index)
{

	if (!SessionSearch.IsValid()) return;
	const auto SessionInterface = OnlineSubsystem->GetSessionInterface();
	if (!SessionInterface.IsValid()) return;
	if (Main != nullptr)
	{
		Main->Teardown();
		
	}

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
	
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Join %s"), *Address));;
	}
	auto pc = GetFirstLocalPlayerController(GetWorld());
	if (pc) {
		pc->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}*/
}

void UMultiplayGameInstance::LoadMainMenu()
{
	auto pc = GetFirstLocalPlayerController(GetWorld());
	if (pc) {
		pc->ClientTravel("/Game/Multiplay_Learn/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
	}
}

void UMultiplayGameInstance::RefreshServerList()
{
	const IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		//SessionSearch->bIsLanQuery = false;
		SessionSearch->MaxSearchResults = 1000000;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		UE_LOG(LogTemp, Warning, TEXT("Start FindSession"));

		const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
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
	const IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
	UE_LOG(LogTemp, Warning, TEXT("Session ID : %s"), *SessionInterface->GetNamedSession(SESSION_NAME)->GetSessionIdStr());
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

void UMultiplayGameInstance::OnFindSessionComplete(bool Success)
{
	if (Success && SessionSearch.IsValid() && Main != nullptr)
	{

		TArray<FString> SessionNames;
		UE_LOG(LogTemp, Warning, TEXT("OnFindSessionComplete : result Num : %d"), SessionSearch->SearchResults.Num());
		for (auto& result : SessionSearch->SearchResults)
		{

			SessionNames.Add(result.GetSessionIdStr());
			UE_LOG(LogTemp, Warning, TEXT("%s"), *result.GetSessionIdStr());
			UE_LOG(LogTemp, Warning, TEXT("id : %s"), *result.Session.OwningUserId.Get()->ToString());
			
			UE_LOG(LogTemp, Warning, TEXT("search Session id : %s"), *result.Session.SessionInfo->GetSessionId().ToString());
		}
		Main->SetServerList(SessionNames);
		UE_LOG(LogTemp, Warning, TEXT("Success FindSession"));
	}
}

void UMultiplayGameInstance::CreateSession()
{
	const IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
	if (SessionInterface.IsValid()) {
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = false;
		SessionSettings.NumPublicConnections = 4;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bAllowJoinInProgress = true;
		SessionSettings.bAllowJoinViaPresence = true;
		SessionSettings.bUsesPresence = true;
		const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
		
	}
}

void UMultiplayGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type ResultType)
{

	const auto SessionInterface = OnlineSubsystem->GetSessionInterface();
	if (!SessionInterface.IsValid()) return;
	FString URL;
	SessionInterface->GetResolvedConnectString(SESSION_NAME, URL);
	UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete ConnectInfo : %s"), *URL);
	auto pc = GetFirstLocalPlayerController(GetWorld());
	if (pc) {
		pc->ClientTravel(URL, ETravelType::TRAVEL_Absolute);
	}
}
