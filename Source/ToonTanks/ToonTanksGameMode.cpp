// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* _deadActor)
{
    if(_deadActor == tank)
    {
        tank->HandleDestruction();

        if(tank->GetTankPlayerController())
        {
            tank->DisableInput(tank->GetTankPlayerController());
            tank->GetTankPlayerController()->bShowMouseCursor = false;
        }
    }
    else if(ATower* destroyedTower = Cast<ATower>(_deadActor))
    {
        destroyedTower->HandleDestruction();
    }
}   

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
}