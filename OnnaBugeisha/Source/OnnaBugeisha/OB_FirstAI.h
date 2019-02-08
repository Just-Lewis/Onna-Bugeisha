// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "OB_FirstAI.generated.h"

/**
 * 
 */
UCLASS()
class ONNABUGEISHA_API AOB_FirstAI : public AAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float deltatime) override;
	APawn *AAI;

	virtual void GetControlledAI();

private:

};
