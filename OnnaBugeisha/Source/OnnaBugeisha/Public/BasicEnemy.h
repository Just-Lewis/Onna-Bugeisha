// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicEnemy.generated.h"
#include "Observer_V1.h"

UCLASS()
class ONNABUGEISHA_API ABasicEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicEnemy();
	//Used to change bool for combat from elsewhere
	void CombatSetter(bool state);
	//Used to notify observer of new states
	void ObserverNotifier(bool state);
	//Used to check if player within a set range
	void PlayerChecker(void);

	//Enemy variables
	int health;
	int aggressionLevel; //Can be used to interpret AI reactions to certain player actions
	float sightValue; //To be used when calculating whether player is in sight range or not of enemy.

private:
	bool inCombat; //Can be changed by observer using CombatSetter function of class. TBC

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	///The below is a design patter for a Subject class. May need changing to be relevant so it is commented out for now.
/*public:
	virtual ~ABasicEnemy();

	virtual void Attach(AObserver_V1*); //Attaches to pointer for Obesrver
	virtual void Detach(AObserver_V1*); //Detaches from pointer
	virtual void Notify(); //Used to notify Observer of changes
	
protected:
	//ABasicEnemy();

private:
	List<AObserver_V1*> *_observers; //List function not working via Unreal. Would need to seek out alternatives
	*/
};
