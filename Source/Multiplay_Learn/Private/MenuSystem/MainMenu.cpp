// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/MainMenu.h"
#include "Components/Button.h"
#include "Multiplay_Learn/MultiplayGameInstance.h"

void UMainMenu::SetMenuInterface(IMenuInterface* menuInterface)
{
	this->MenuInterface = menuInterface;
}

void UMainMenu::Setup()
{
	this->AddToViewport();

	auto pc = GetWorld()->GetFirstPlayerController();
	if (pc) {
		FInputModeUIOnly InputModeData;
		InputModeData.SetWidgetToFocus(this->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		pc->SetInputMode(InputModeData);
		pc->bShowMouseCursor = true;
	}
}

void UMainMenu::Teardown()
{
	auto pc = GetWorld()->GetFirstPlayerController();
	if (pc) {
		FInputModeGameOnly InputModeData;
		pc->SetInputMode(InputModeData);
		pc->bShowMouseCursor = false;
	}
	this->RemoveFromParent();
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
