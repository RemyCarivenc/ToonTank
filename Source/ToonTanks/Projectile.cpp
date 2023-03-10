// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Mesh");
	RootComponent = projectileMesh;

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	projectileMovementComponent->MaxSpeed = 1300.0f;
	projectileMovementComponent->InitialSpeed = 1300.0f;

	trailParticles = CreateDefaultSubobject<UParticleSystemComponent>("Smoke Trail");
	trailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	projectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (launchSound)
		UGameplayStatics::PlaySoundAtLocation(this, launchSound, GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent *_hitComp, AActor *_otherActor, UPrimitiveComponent *_otherComp, FVector _normalImpulse, const FHitResult &_hit)
{
	AActor* myOwner = GetOwner();
	if (myOwner == nullptr)
	{
		Destroy();
		return;
	}

	AController* myOwnerInstigator = myOwner->GetInstigatorController();
	UClass* damageTypeClass = UDamageType::StaticClass();

	if (_otherActor && _otherActor != this && _otherActor != myOwner)
	{
		UGameplayStatics::ApplyDamage(_otherActor, damage, myOwnerInstigator, this, damageTypeClass);

		if (hitParticles)
			UGameplayStatics::SpawnEmitterAtLocation(this, hitParticles, GetActorLocation(), GetActorRotation());

		if (hitSound)
			UGameplayStatics::PlaySoundAtLocation(this, hitSound, GetActorLocation());

		if(hitCameraShakeClass)
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(hitCameraShakeClass);

	}
	Destroy();
}
