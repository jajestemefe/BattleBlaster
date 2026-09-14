// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"

#include "Tank.h"

#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float FireRange = 300.f;

	UPROPERTY(EditAnywhere)
	float FireRate = 2.f;

	ATank* Tank;

	void CheckFireCondition();
	bool IsInFireRange();
	
	void HandleDestruction();
};
