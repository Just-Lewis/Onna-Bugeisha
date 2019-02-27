// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Classes/Engine/World.h" //needed for world functions (getworld)
#include "GameFramework/PlayerController.h" //Needed to assign target pawn using "Player()->GetPawn()"
#include "OB_FirstAI.generated.h"

/**
 *
 */
	UCLASS()
	class ONNABUGEISHA_API AOB_FirstAI : public AAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override; //override ensures parents with beginplay are not overwritten by this function, Virtual allows child classes to have self made begin plays too.
	virtual void Tick(float deltatime) override;


	void GetControlledAIPawn(); //sets self pawn
	void GetTargetPawn(); //sets target pawn

private:

	APawn *SelfPawn = nullptr; //protection
	APawn *TargetPawn = nullptr; //protection

};