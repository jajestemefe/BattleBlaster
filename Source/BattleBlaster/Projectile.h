// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Projectile.generated.h"

UCLASS()
class BATTLEBLASTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileMesh;
	
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComp;
	
	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* TrailParticles;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* HitParticles;
	
	UPROPERTY(EditAnywhere)
	USoundBase* LaunchSound;
	
	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;
	
	UPROPERTY(EditAnywhere)
	float Damage = 25.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
