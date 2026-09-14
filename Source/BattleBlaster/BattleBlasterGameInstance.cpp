// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameInstance.h"

#include "InterchangeFactoryBase.h"
#include "Kismet/GameplayStatics.h"

void UBattleBlasterGameInstance::LoadNextLevel()
{
	if (CurrentLevelIndex < LastLevelIndex)
	{
		ChangeLevel(CurrentLevelIndex+1);
	}
	else
	{
		RestartGame();
	}
}

void UBattleBlasterGameInstance::RestartCurrentLevel()
{
	ChangeLevel(CurrentLevelIndex);
}

void UBattleBlasterGameInstance::RestartGame()
{
	ChangeLevel(1);
}

void UBattleBlasterGameInstance::ChangeLevel(int32 NewLevelIndex)
{
	if (NewLevelIndex > 0 && NewLevelIndex <= LastLevelIndex)
	{
		CurrentLevelIndex = NewLevelIndex;
		
		FString LevelNameString = FString::Printf(TEXT("Level_%d"), CurrentLevelIndex); 
		UGameplayStatics::OpenLevel(GetWorld(), *LevelNameString);
	}
}
