// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicEnemy.h"

// Sets default values
ABasicEnemy::ABasicEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

///The below is a design patter for a Subject class. May need changing to be relevant so it is commented out for now.
/*
//Used to attach observers to basic enemy
void ABasicEnemy::Attach(AObserver_V1* o)
{
	_observers->Append(o);
}

//Used to detach observers from basic enemy
void ABasicEnemy::Detach(AObserver_V1* o)
{
	_observers->Remove(o);
}

//Notification code to Observers
void ABasicEnemy::Notify()
{
	ListIterator<AObserver_V1*> i(_observers);

	for (i.First(); !i.IsDone(); i.Next())
	{
		i.CurrentItem()->Update(this);
	}
}
*/

//Used to change enemy combat state
void ABasicEnemy::CombatSetter(bool state)
{
	inCombat = state;
}

void ABasicEnemy::ObserverNotifier(bool state)
{
	//Code for notifying the Observer of the change goes here.
}

void ABasicEnemy::PlayerChecker(void)
{
	//Code for checking if player is within certain area/section of map to enemy. if true, notifier needs to be called to update the observer to then update all other enemies
	//if (**Player class is within sight value**)
	//{
	//ObserverNotifier(true);
	//}
}

