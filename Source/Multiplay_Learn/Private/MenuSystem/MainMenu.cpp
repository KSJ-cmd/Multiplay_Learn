// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/MainMenu.h"
#include "Components/Button.h"
#include "Multiplay_Learn/MultiplayGameInstance.h"

bool UMainMenu::Initialize()
{

	Host->OnClicked.AddDynamic(this, &UMainMenu::host);
	Join->OnClicked.AddDynamic(this, &UMainMenu::join);

	return Super::Initialize();
}

void UMainMenu::host()
{
	auto GI = Cast<UMultiplayGameInstance>(GetGameInstance());
	if(!GI)
	{
		UE_LOG(LogTemp, Warning, 
			TEXT("GameInstance nullptr : MainMenu Host Button"));
	}
	GI->Host();
}

void UMainMenu::join()
{
	auto GI = Cast<UMultiplayGameInstance>(GetGameInstance());
	if (!GI)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("GameInstance nullptr : MainMenu Join Button"));
	}
	GI->Join("175.204.64.29");
}
