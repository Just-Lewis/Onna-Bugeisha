-// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OB_PlayerControllerV1.generated.h"

/**
 *
 */
	UCLASS()
	class ONNABUGEISHA_API AOB_PlayerControllerV1 : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

private:

};