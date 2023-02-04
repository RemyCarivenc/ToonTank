// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

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
    PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);

    PlayerInputComponent->BindAction("Fire",IE_Pressed,this, &ATank::Fire);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    Super::BeginPlay();

    tankPlayerController = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (tankPlayerController)
    {
        FHitResult hitResult;
        tankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);

        RotateTurret(hitResult.ImpactPoint);
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}

void ATank::Move(float _value)
{
    AddActorWorldOffset(GetActorForwardVector() * _value * speed * UGameplayStatics::GetWorldDeltaSeconds(this), true);
}

void ATank::Turn(float _value)
{
    FRotator deltaRotation = FRotator::ZeroRotator;
    deltaRotation.Yaw = _value * turnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorWorldRotation(deltaRotation);
}
