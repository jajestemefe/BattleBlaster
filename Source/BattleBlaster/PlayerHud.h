// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "PlayerHud.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API UPlayerHud : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TurretCountTextBlock;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* PlayerHealthProgressBar;
	
	void SetMessageText(FString Message);
	void SetPlayerHealthPercentage(float PlayerHealthPercentage);
};
