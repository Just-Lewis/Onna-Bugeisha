// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OnnaBugeishaCharacter.generated.h"

UCLASS(config=Game)
class AOnnaBugeishaCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AOnnaBugeishaCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//Our variables
	int maxHealth;
	int currentHealth;
	
	int playerLevel; //Allows us to have levelling systems in place

	bool inCombat; //True = combat mode and false = non-attack mode

	FString niceness = "yeah it's working";


	//These are so we can use them in the blueprint to call animations. Category might not be correct
	UPROPERTY(BlueprintReadOnly, Category = Character)
	uint32 bPressedAttackLight : 1;

	UPROPERTY(BlueprintReadOnly, Category = Character)
	uint32 bPressedAttackHeavy : 1;

	UPROPERTY(BlueprintReadOnly, Category = Character)
	uint32 bPressedGuard : 1;

	UPROPERTY(BlueprintReadOnly, Category = Character)
	uint32 bPressedRoll : 1;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);


	//////////////////////////////Onna Bugesiah Stuff ///////////////////////////

	void AttackLight();
	void AttackHeavy();
	void AttackHeavyStop();
	void Guard();
	void GuardStop();
	void Roll();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

