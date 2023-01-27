// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATank::ATank()
{
    springArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    springArm->SetupAttachment(RootComponent);

    camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    camera->SetupAttachment(springArm);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
}

void ATank::Move(float _value)
{
}
