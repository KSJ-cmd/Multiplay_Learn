// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/MainMenu.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetSwitcher.h"
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
	if(!HostButton) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::UMainMenu::HostServer);
	if (!JoinButton) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::UMainMenu::OpenJoinMenu);
	if (!CancelButton) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::CancelMenu);
	if (!AddressButton) return false;
	AddressButton->OnClicked.AddDynamic(this, &UMainMenu::IPJoin);
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

void UMainMenu::OpenJoinMenu()
{
	if (!MenuInterface)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("GameInstance nullptr : MainMenu Join Button"));
	}
	MenuSwitcher->SetActiveWidget(JoinMenu);
	//MenuInterface->Join();
}

void UMainMenu::CancelMenu()
{
	if(MenuSwitcher==nullptr)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("GameInstance nullptr : Input_Join_IP_Menu Switcher"));
		return;
	}
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::IPJoin()
{
	if (!MenuInterface)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("GameInstance nullptr : MainMenu IPJoin Button"));
	}
	if (!AddressInput) return;
	auto address = AddressInput->GetText();
	MenuInterface->Join(address.ToString());
	
}
