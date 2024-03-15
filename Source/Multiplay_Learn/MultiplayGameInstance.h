// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "MultiplayGameInstance.generated.h"

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
	void LoadMenu();

	UFUNCTION()
	virtual void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& Address);

private:
	TSubclassOf<class UUserWidget> MainMenuClass;

	class UMainMenu* Menu;
};
