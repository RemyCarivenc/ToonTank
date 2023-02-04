// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UParticleSystem;
class UParticleSystemComponent;
class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent *projectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent *projectileMovementComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *_hitComp, AActor *_otherActor, UPrimitiveComponent *_otherComp, FVector _normalImpulse, const FHitResult &_hit);

	UPROPERTY(EditAnywhere)
	float damage = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem *hitParticles;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	UParticleSystemComponent *trailParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase *launchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase *hitSound;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
