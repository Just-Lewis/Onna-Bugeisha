// Fill out your copyright notice in the Description page of Project Settings.

#include "OB_PlayerController.h"
#include "../Public/OB_PlayerController.h"

void AOB_PlayerController::BeginPlay() {

	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("beginPlay acheived in OB_PlayerController "));

}

void AOB_PlayerController::PlayerGetPawn()
{
	Pawn = GetCharacter();
}
