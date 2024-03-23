// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "Multiplay_Learn/MultiplayGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	++NumberOfPlayers;
	if(NumberOfPlayers>=2)
	{
		GetWorldTimerManager().SetTimer(SessionTimerHandle, this, &ALobbyGameMode::StartGame, 10);
		UE_LOG(LogTemp, Warning, TEXT("Reached 2 Players"));
		
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	--NumberOfPlayers;
}

void ALobbyGameMode::StartGame()
{
	auto GI = Cast<UMultiplayGameInstance>(GetGameInstance());
	auto world = GetWorld();
	if (world != nullptr && GI != nullptr)
	{
		GI->StartSession();
		bUseSeamlessTravel = true;
		world->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
	}

}
