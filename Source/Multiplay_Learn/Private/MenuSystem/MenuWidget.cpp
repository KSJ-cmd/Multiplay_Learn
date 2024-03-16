// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/MenuWidget.h"

void UMenuWidget::SetMenuInterface(IMenuInterface* menuInterface)
{
	this->MenuInterface = menuInterface;
}

void UMenuWidget::Setup()
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

void UMenuWidget::Teardown()
{
	auto pc = GetWorld()->GetFirstPlayerController();
	if (pc) {
		FInputModeGameOnly InputModeData;
		pc->SetInputMode(InputModeData);
		pc->bShowMouseCursor = false;
	}
	this->RemoveFromParent();
}
