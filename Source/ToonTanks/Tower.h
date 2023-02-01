// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class ATank *tank;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float fireRange = 300.f;

	FTimerHandle fireRateTimerHandle;
	float fireRate = 2.f;
	void CheckFireCondition();

	bool InFireRange();
};
