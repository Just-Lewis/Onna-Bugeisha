// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_OB_CheckForPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "OnnaBugeishaCharacter.h"
#include "BasicWolfTestEnemy.h"
#include "OB_FirstAI.h"


UBTService_OB_CheckForPlayer::UBTService_OB_CheckForPlayer()
{
	bCreateNodeInstance = true; //needed for multiple AI's
}

void UBTService_OB_CheckForPlayer::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	AOB_FirstAI *EnemyPC = Cast<AOB_FirstAI>(OwnerComp.GetAIOwner()); //get ai controller class

	if (EnemyPC) 
	{
		AOnnaBugeishaCharacter *Enemy = Cast< AOnnaBugeishaCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()); //Compiles okay even though it shows as error...
		
		if (Enemy) {
			//assign blackboard component
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyPC->EnemyKeyID,Enemy);

		}
		
	}
}
