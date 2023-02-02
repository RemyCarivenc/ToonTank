// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const {return tankPlayerController;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent *springArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent *camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float speed = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float turnRate = 45.0f;

	void Move(float _value);
	void Turn(float _value);

	APlayerController* tankPlayerController;

};
