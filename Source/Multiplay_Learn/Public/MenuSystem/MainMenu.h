// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

class UEditableTextBox;
class UWidgetSwitcher;


USTRUCT()
struct FServerData
{
	GENERATED_BODY()
public:
	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUserName;
};
/**
 * 
 */
UCLASS()
class MULTIPLAY_LEARN_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	void SetServerList(TArray<FServerData> ServerNames);

	void UpdateChildren();
	void SeleceIndex(uint32 index);
protected:
	virtual bool Initialize() override;
private:
	//MainMenu
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	//JoinMenu
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* AddressButton;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList;

	//HostMenu
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* InputHostName;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConfirmHostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelHostButton;

	//Menu ptr
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;

	
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;



	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void Quit();

	UFUNCTION()
	void CancelMenu();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void ConfirmHost();

	UFUNCTION()
	void CancelHost();
	
	TSubclassOf<class UUserWidget> ServerRowClass;

	TOptional<uint32> SelectedIndex;
};
