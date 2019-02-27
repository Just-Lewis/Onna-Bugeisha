// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OnnaBugeishaCharacter.h"
#include "OB_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ONNABUGEISHA_API AOB_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	void PlayerGetPawn();

private:

	ACharacter *Pawn = nullptr;
	
	
};