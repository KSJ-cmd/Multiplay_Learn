// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/MenuWidget.h"
#include "InGameMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class MULTIPLAY_LEARN_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()
public:
protected:
	virtual bool Initialize() override;
private:

	UPROPERTY(meta =(BindWidget))
	UButton* ToMainButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ReturnButton;

	UFUNCTION()
	void ToMain();

	UFUNCTION()
	void ReturnGame();
};
