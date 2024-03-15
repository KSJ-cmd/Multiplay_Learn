// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/MainMenu.h"
#include "Components/Button.h"
#include "Multiplay_Learn/MultiplayGameInstance.h"

void UMainMenu::SetMenuInterface(IMenuInterface* menuInterface)
{
	this->MenuInterface = menuInterface;
}

bool UMainMenu::Initialize()
{
	auto success = Super::Initialize();
	if (!success) return false;

	Host->OnClicked.AddDynamic(this, &UMainMenu::UMainMenu::HostServer);
	//Join->OnClicked.AddDynamic(this, &UMainMenu::join);
	
	return true;
}

void UMainMenu::HostServer()
{

	if(!MenuInterface)
	{
		UE_LOG(LogTemp, Warning, 
			TEXT("GameInstance nullptr : MainMenu Host Button"));
	}
	MenuInterface->Host();
}

void UMainMenu::JoinServer()
{
	if (!MenuInterface)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("GameInstance nullptr : MainMenu Join Button"));
	}
	//MenuInterface->Join();
}
