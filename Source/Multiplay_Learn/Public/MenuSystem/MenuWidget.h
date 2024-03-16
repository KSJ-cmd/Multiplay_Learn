// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class IMenuInterface;
/**
 * 
 */
UCLASS()
class MULTIPLAY_LEARN_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetMenuInterface(IMenuInterface* menuInterface);

	void Setup();
	void Teardown();
protected:

	IMenuInterface* MenuInterface;
};
