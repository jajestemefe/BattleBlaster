// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Tower.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	SetRootComponent(ProjectileMesh);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->InitialSpeed = 2000.f;
	ProjectileMovementComp->MaxSpeed = 2000.f;
	
	TrailParticles = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailParticles"));
	TrailParticles->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaunchSound, GetActorLocation(), GetActorRotation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Display, TEXT("Projectile it: %s"), *OtherActor->GetActorNameOrLabel());
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		if (OtherActor && (OtherActor != MyOwner) && (OtherActor != this))
		{
			if (Cast<ATower>(OtherActor) && Cast<ATower>(MyOwner))
			{
			}
			else
			{
				UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), 
					this, UDamageType::StaticClass());
			}
			
			if (HitParticles && HitSound)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitParticles, GetActorLocation(), GetActorRotation()); 
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation(), GetActorRotation(),
					1.f,2.f);
			}
			
			if (HitCameraShakeClass)
			{
				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				if (PlayerController)
				{
					PlayerController->ClientStartCameraShake(HitCameraShakeClass);
				}
			}
			
		}
	}
	
	Destroy();
}

