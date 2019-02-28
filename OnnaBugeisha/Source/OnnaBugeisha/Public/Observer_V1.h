// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "BasicEnemy.h"
#include "Observer_V1.generated.h"


/**
 * 
 */
UCLASS()
class ONNABUGEISHA_API AObserver_V1 : public AWorldSettings
{
	GENERATED_BODY()
	

		///The below is a design patter for a Subject class. May need changing to be relevant so it is commented out for now.
		/*
public:
	virtual ~AObserver_V1();
	virtual void Update(ABasicEnemy* theChangedSubject) = 0;

protected:
	AObserver_V1();
	*/
};
