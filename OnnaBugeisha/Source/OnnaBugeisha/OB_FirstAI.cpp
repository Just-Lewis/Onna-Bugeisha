// Fill out your copyright notice in the Description page of Project Settings.

#include "OB_FirstAI.h"

void AOB_FirstAI::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("ai has started"));
	GetControlledAI();
}

void AOB_FirstAI::Tick(float deltatime)
{
	Super::Tick(deltatime);
	UE_LOG(LogTemp, Error, TEXT("ai is ticking"));
}

void AOB_FirstAI::GetControlledAI() {
	
		if (GetPawn() == nullptr) { UE_LOG(LogTemp, Error, TEXT("missing pointer"))AAI = nullptr; }
		AAI = GetPawn();

		UE_LOG(LogTemp, Error, TEXT("ai controller is %s"), AAI);

};