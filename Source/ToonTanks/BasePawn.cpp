// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>("Capsule collider");
	RootComponent = capsuleComp;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	baseMesh->SetupAttachment(capsuleComp);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Spawn Point");
	projectileSpawnPoint->SetupAttachment(turretMesh);
}

void ABasePawn::HandleDestruction()
{	
	if(deathParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this, deathParticles, GetActorLocation(), GetActorRotation());

	if (deathSound)
		UGameplayStatics::PlaySoundAtLocation(this, deathSound, GetActorLocation());
	
	if(deathCameraShakeClass)
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(deathCameraShakeClass);
}

void ABasePawn::RotateTurret(FVector _lookAtTarget)
{
	FVector toTarget = _lookAtTarget - turretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(.0f, toTarget.Rotation().Yaw, .0f);
	turretMesh->SetWorldRotation(FMath::RInterpTo(turretMesh->GetComponentRotation(), lookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 10.0f));
}

void ABasePawn::Fire()
{
	FVector location = projectileSpawnPoint->GetComponentLocation();
	FRotator rotation = projectileSpawnPoint->GetComponentRotation();

	auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileClass, location, rotation);
	projectile->SetOwner(this);
}