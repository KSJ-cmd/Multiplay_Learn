// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/MainMenu.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetSwitcher.h"
#include "MenuSystem/ServerRow.h"
#include "Multiplay_Learn/MultiplayGameInstance.h"


UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (ServerRowBPClass.Class != nullptr)
	{
		ServerRowClass = ServerRowBPClass.Class;
	}
}

bool UMainMenu::Initialize()
{
	auto success = Super::Initialize();
	if (!success) return false;

	if(!HostButton) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!JoinButton) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!QuitButton) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::Quit);

	if (!CancelButton) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::CancelMenu);

	if (!AddressButton) return false;
	AddressButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

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

void UMainMenu::Quit()
{
	auto pc = GetWorld()->GetFirstPlayerController();
	if(pc)
	{
		pc->ConsoleCommand("quit");
	}
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

void UMainMenu::JoinServer()
{
	if (!MenuInterface)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("GameInstance nullptr : MainMenu IPJoin Button"));

		UServerRow* Row = CreateWidget<UServerRow>(GetWorld(), ServerRowClass);
		if(Row)
		{
			ServerList->AddChild(Row);
		}
	}
	//if (!AddressInput) return;
	//auto address = AddressInput->GetText();
	//MenuInterface->Join(address.ToString());
	
}
