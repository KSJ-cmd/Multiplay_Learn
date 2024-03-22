// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class MULTIPLAY_LEARN_API UServerRow : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ServerName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HostName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ServerPersons;
	UPROPERTY(meta = (BindWidget))
	UButton* SelectButton;

	UPROPERTY(BlueprintReadOnly)
	bool isSelected = false;

	void Setup(class UMainMenu* Parent, uint32 Index);
protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void ServerSelect();

	uint32 ServerIndex;

	UPROPERTY()
	class UMainMenu* MainMenu;
};
