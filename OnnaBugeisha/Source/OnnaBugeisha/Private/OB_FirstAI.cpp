// Fill out your copyright notice in the Description page of Project Settings.

#include "OB_FirstAI.h"

void AOB_FirstAI::BeginPlay()
{
	Super::BeginPlay(); //to make sure parents with BeginPlay run first.
	//UE_LOG(LogTemp, Warning, TEXT("ai has started"));
	GetControlledAIPawn();
	GetTargetPawn();
}

void AOB_FirstAI::Tick(float deltatime)
{
	Super::Tick(deltatime);


}

void AOB_FirstAI::GetControlledAIPawn() {

	if (GetPawn() == nullptr) //protection and log
	{
		UE_LOG(LogTemp, Warning, TEXT("missing pointer to self in AI - %s"), *this->GetName());
		SelfPawn = nullptr;
		return;
	}

	//else	
	SelfPawn = GetPawn();
	//UE_LOG(LogTemp, Warning, TEXT("ai %s controller is %s"), *this->GetName(), *SelfPawn->GetName());

}
void AOB_FirstAI::GetTargetPawn()
{
	if (GetWorld()->GetFirstPlayerController()->GetPawn() == nullptr) //protection and log
	{
		UE_LOG(LogTemp, Warning, TEXT("%s ai is missing target pointer"), *this->GetName());
		return;
	}

	//else
	TargetPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	//UE_LOG(LogTemp, Warning, TEXT("ai %s targetting is %s"), *this->GetName(), *TargetPawn->GetName());
}
;