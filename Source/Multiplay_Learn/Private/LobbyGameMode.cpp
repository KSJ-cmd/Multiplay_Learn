// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	++NumberOfPlayers;
	if(NumberOfPlayers>=2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Reached 2 Players"));
		auto world = GetWorld();
		if (world)
		{
			bUseSeamlessTravel = true;
			world->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
		}
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	--NumberOfPlayers;
}
