
// Fill out your copyright notice in the Description page of Project Settings.

#include "OB_AICLassV1.h"

void AOB_AICLassV1::BeginPlay()
{
	Super::BeginPlay(); //to make sure parents with BeginPlay run first.
	UE_LOG(LogTemp, Error, TEXT("ai has started"));
	GetControlledAIPawn();
	GetTargetPawn();
}

void AOB_AICLassV1::Tick(float deltatime)
{
	Super::Tick(deltatime);

}

void AOB_AICLassV1::GetControlledAIPawn() {

	if (GetPawn() == nullptr) //protection and log
	{
		UE_LOG(LogTemp, Error, TEXT("missing pointer to self in AI - %s"), *this->GetName());
		SelfPawn = nullptr;
		return;
	}

	//else	
	SelfPawn = GetPawn();
	UE_LOG(LogTemp, Error, TEXT("ai %s controller is %s"), *this->GetName(), *SelfPawn->GetName());

}
void AOB_AICLassV1::GetTargetPawn()
{
	if (GetWorld()->GetFirstPlayerController()->GetPawn() == nullptr) //protection and log
	{
		UE_LOG(LogTemp, Error, TEXT("%s ai is missing target pointer"), *this->GetName());
		return;
	}

	//else
	TargetPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	UE_LOG(LogTemp, Error, TEXT("ai %s targetting is %s"), *this->GetName(), *TargetPawn->GetName());
}
;