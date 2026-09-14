// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"

#include "GameFramework/SpringArmComponent.h"
//#include "Camera/CameraComponent.h"

//#include "InputMappingcontext.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"

#include "Tank.generated.h"


/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireAction;


	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 600.f;

	UPROPERTY(EditAnywhere)
	float TurnSpeed = 400.f;
	
	APlayerController* PlayerController;

	bool IsAlive = true;
	
	void MoveInput(const FInputActionValue& Value);

	void TurnInput(const FInputActionValue& Value);

	void HandleDestruction();
	
	void SetPlayerEnabled(bool Enabled);
	
};
