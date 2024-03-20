// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/ServerRow.h"

#include "Components/Button.h"
#include "MenuSystem/MainMenu.h"
void UServerRow::Setup(UMainMenu* Parent, uint32 Index)
{
	MainMenu = Parent;
	ServerIndex = Index;
}

bool UServerRow::Initialize()
{
	bool success = Super::Initialize();
	if (!success) return false;

	if (SelectButton != nullptr)
	{
		SelectButton->OnClicked.AddDynamic(this, &UServerRow::ServerSelect);
	}
	return true;
}

void UServerRow::ServerSelect()
{
	if (MainMenu != nullptr)
		MainMenu->SeleceIndex(ServerIndex);
}
