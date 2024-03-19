// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "MultiplayGameInstance.generated.h"

class FOnlineSessionSearch;
class IOnlineSubsystem;
/**
 * 
 */
UCLASS()
class MULTIPLAY_LEARN_API UMultiplayGameInstance : public UGameInstance,public IMenuInterface
{
	GENERATED_BODY()
public:
	UMultiplayGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void LoadMenuWidget();
	UFUNCTION(BlueprintCallable)
	void LoadInGameMenu();

	UFUNCTION()
	virtual void Host() override;

	UFUNCTION(Exec)
	virtual void Join(const FString& Address) override;

	UFUNCTION()
	virtual void LoadMainMenu() override;

private:
	TSubclassOf<class UUserWidget> MainMenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu* Main;
	class UInGameMenu* InGame;
	IOnlineSubsystem* OnlineSubsystem;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionComplete(bool Success);
	void CreateSession();
};
