// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_OB_MoveToPlayer.h"
#include "OB_FirstAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "OB_FirstAI.h"
#include "OnnaBugeishaCharacter.h"
#include "BasicWolfTestEnemy.h"



EBTNodeResult::Type UBTTask_OB_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	
	AOB_FirstAI *CharPC = Cast<AOB_FirstAI>(OwnerComp.GetAIOwner());
	if (CharPC) {
		AOnnaBugeishaCharacter *Enemy = Cast<AOnnaBugeishaCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPC->EnemyKeyID));

		if (Enemy)
		{
			CharPC->MoveToActor(Enemy, 5.f, true, true, true, 0, true);
			return EBTNodeResult::Succeeded;
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}

	return EBTNodeResult::Failed;
}