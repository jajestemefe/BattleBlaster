// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"

#include <string>

#include "Kismet/GameplayStatics.h"
#include "BattleBlasterGameInstance.h"
//#include "Tower.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);
	TowerCount = Towers.Num();
	UE_LOG(LogTemp, Display, TEXT("Number of towers: %d"), TowerCount);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		Tank = Cast<ATank>(PlayerPawn);
		if (!Tank)
		{
			UE_LOG(LogTemp, Display, TEXT("GameMode: Failed to find the Tank actor!"));
		}

	}

	int32 i = 0;
	while (i < TowerCount)
	{
		AActor* TowerActor = Towers[i];
		ATower* Tower = Cast<ATower>(TowerActor);
		if (Tower && Tank)
		{
			Tower->Tank = Tank;
			UE_LOG(LogTemp, Display, TEXT("%s setting the tank..."), *Tower->GetActorNameOrLabel());
		}

		i++;
	}
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		ScreenMessageWidget = CreateWidget<UScreenMessage>(PlayerController, ScreenMessageClass);
		if (ScreenMessageWidget)
		{
			ScreenMessageWidget->AddToPlayerScreen();
			ScreenMessageWidget->SetMessageText("Get Ready!");
		}
	}
	
	CountdownSeconds = CountdownDelay;
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this,
		&ABattleBlasterGameMode::OnCountdownTimerTimeout, 1.0f, true);
	
}

void ABattleBlasterGameMode::OnCountdownTimerTimeout()
{
	
	if (CountdownSeconds > 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Countdown: %d"), CountdownSeconds);
		ScreenMessageWidget->SetMessageText(FString::FromInt(CountdownSeconds));
	}
	else if (CountdownSeconds == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Go!"));
		ScreenMessageWidget->SetMessageText("Go!");
		Tank->SetPlayerEnabled(true);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		UE_LOG(LogTemp, Display, TEXT("timer Cleared!"));
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	CountdownSeconds -= 1;
	
}

void ABattleBlasterGameMode::ActorDied(AActor* DeadActor)
{
	bool IsGameOver = false;
	
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		IsGameOver = true;
	}
	else
	{
		ATower* DeadTower = Cast<ATower>(DeadActor);
		if (DeadTower)
		{
			DeadTower->HandleDestruction();
			
			TowerCount--;
			if (TowerCount == 0)
			{
				IsGameOver = true;
				IsVictory = true;
			}
		}
	}
	
	if (IsGameOver)
	{
		FString GameOverString = IsVictory ? "Victory!" : "Defeat!";
		
		ScreenMessageWidget->SetMessageText(GameOverString);
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Display, TEXT("Game Over: %s"), *GameOverString);
		
		FTimerHandle GameOverTimerHandle;
		GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, 
			&ABattleBlasterGameMode::OnGameOverTimertimeout, GameOverDelay, false);
	}
}

void ABattleBlasterGameMode::OnGameOverTimertimeout()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UBattleBlasterGameInstance* BattleBlasterGameInstance =
			Cast<UBattleBlasterGameInstance>(GameInstance);
		if (BattleBlasterGameInstance)
		{
			if (IsVictory)
			{
				BattleBlasterGameInstance->LoadNextLevel();
			}
			else
			{
				BattleBlasterGameInstance->RestartCurrentLevel();
			}
		}
	}
	
}

