// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/InGameMenu.h"
#include "MenuSystem/MenuInterface.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	bool success = Super::Initialize();
	if (!success) return false;

	if (!ToMainButton) return false;
	ToMainButton->OnClicked.AddDynamic(this, &UInGameMenu::ToMain);
	if (!ReturnButton) return false;
	ReturnButton->OnClicked.AddDynamic(this, &UInGameMenu::ReturnGame);

	return true;
}

void UInGameMenu::ToMain()
{
	if (MenuInterface != nullptr) {
		Teardown();
		MenuInterface->LoadMainMenu();
	}
}

void UInGameMenu::ReturnGame()
{
	Teardown();
}
