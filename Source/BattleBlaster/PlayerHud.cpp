// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"

void UPlayerHud::SetMessageText(FString Message)
{
	FText MessageText = FText::FromString(Message);
	TurretCountTextBlock->SetText(MessageText);
}

void UPlayerHud::SetPlayerHealthPercentage(float PlayerHealthPercentage)
{
	PlayerHealthProgressBar->SetPercent(PlayerHealthPercentage);
}
