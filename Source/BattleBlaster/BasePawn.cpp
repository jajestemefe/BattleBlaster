// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector VectorToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, VectorToTarget.Rotation().Yaw, 0.f);

	FRotator InterpolatedRotation = FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		LookAtRotation,
		GetWorld()->GetDeltaSeconds(),
		10.f
	);

	TurretMesh->SetWorldRotation(InterpolatedRotation);
}

void ABasePawn::Fire()
{
	FVector  SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

	//DrawDebugSphere(GetWorld(), SpawnLocation, 25, 16, FColor::Red, false, 3.f);

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	if (Projectile)
	{
		Projectile->SetOwner(this);
	}
}

void ABasePawn::HandleDestruction()
{
	if (DeathParticles && DeathSound)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathParticles, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation(), GetActorRotation());
	}
	if (DeathCameraShakeClass)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			PlayerController->ClientStartCameraShake(DeathCameraShakeClass);
		}
	}
}



