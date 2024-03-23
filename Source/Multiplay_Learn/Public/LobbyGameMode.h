// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Multiplay_Learn/Multiplay_LearnGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAY_LEARN_API ALobbyGameMode : public AMultiplay_LearnGameMode
{
	GENERATED_BODY()
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
private:
	uint32 NumberOfPlayers=0;
};
