// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/MainMenu.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
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

void UMainMenu::SetServerList(TArray<FServerData> ServerNames)
{

	ServerList->ClearChildren();
	uint32 index = 0;
	for (auto& Data : ServerNames)
	{
		UServerRow* Row = CreateWidget<UServerRow>(GetWorld(), ServerRowClass);
		if (Row)
		{
			Row->ServerName->SetText(FText::FromString(Data.Name));
			Row->HostName->SetText(FText::FromString(Data.HostUserName));
			Row->ServerPersons->SetText(
				FText::FromString(
					FString::Printf(TEXT("%d/%d"), Data.CurrentPlayers, Data.MaxPlayers)
				)
			);
			Row->Setup(this, index);
			++index;
			ServerList->AddChild(Row);
		}
	}


}

void UMainMenu::UpdateChildren()
{
	
	for(int i =0;i<ServerList->GetChildrenCount();++i)
	{
		auto Row = Cast<UServerRow>(ServerList->GetChildAt(i));

		if(Row!=nullptr)
		{
			Row->isSelected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
	
		}
	}
}

void UMainMenu::SeleceIndex(uint32 index)
{
	SelectedIndex = index;
	UpdateChildren();
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
	MenuInterface->RefreshServerList();
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
	if (SelectedIndex.IsSet() && MenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index not set"));

	}
};
