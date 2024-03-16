// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

class UEditableTextBox;
class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class MULTIPLAY_LEARN_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

	
protected:
	virtual bool Initialize() override;
private:

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* AddressButton;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* AddressInput;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();


	UFUNCTION()
	void CancelMenu();

	UFUNCTION()
	void IPJoin();

};
