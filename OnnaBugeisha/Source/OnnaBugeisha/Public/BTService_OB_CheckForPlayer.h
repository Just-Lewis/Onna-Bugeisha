// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_OB_CheckForPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ONNABUGEISHA_API UBTService_OB_CheckForPlayer : public UBTService
{
	GENERATED_BODY()

public:

	UBTService_OB_CheckForPlayer();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override; //please don't ask	
	
};
