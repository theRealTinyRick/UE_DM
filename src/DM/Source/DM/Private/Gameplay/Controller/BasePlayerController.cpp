// Fill out your copyright notice in the Description page of Project Settings.


#include <Gameplay/Controller/BasePlayerController.h>

void ABasePlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();

	OnReceivedPlayer();
}
