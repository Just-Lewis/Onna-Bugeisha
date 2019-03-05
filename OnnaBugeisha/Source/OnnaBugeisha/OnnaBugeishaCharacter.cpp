// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "OnnaBugeishaCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AOnnaBugeishaCharacter

AOnnaBugeishaCharacter::AOnnaBugeishaCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	dPlayerLevel = 1;

	HeavyCharge = 0;
	UneffectedDamageMultiplier = 1;
	DamageMulitplier = UneffectedDamageMultiplier;
	SprintMultiplier = 1.5;
	fMaxHealth = 100;
	fCurrentHealth = fMaxHealth;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AOnnaBugeishaCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AOnnaBugeishaCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AOnnaBugeishaCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AOnnaBugeishaCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AOnnaBugeishaCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AOnnaBugeishaCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AOnnaBugeishaCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AOnnaBugeishaCharacter::OnResetVR);


	/////////////////////////////Onna Bugeisha/////////////////////////

	// Set up gameplay OB key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("AttackLight", IE_Pressed, this, &AOnnaBugeishaCharacter::AttackLight);

	PlayerInputComponent->BindAction("AttackHeavy", IE_Pressed, this, &AOnnaBugeishaCharacter::AttackHeavy);
	PlayerInputComponent->BindAction("AttackHeavy", IE_Released, this, &AOnnaBugeishaCharacter::AttackHeavyStop); //need to stop this for charged attack

	PlayerInputComponent->BindAction("Guard", IE_Pressed, this, &AOnnaBugeishaCharacter::Guard);
	PlayerInputComponent->BindAction("Guard", IE_Released, this, &AOnnaBugeishaCharacter::GuardStop);

	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &AOnnaBugeishaCharacter::Roll);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AOnnaBugeishaCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AOnnaBugeishaCharacter::SprintStop);

}


void AOnnaBugeishaCharacter::AttackLight()
{
	bPressedAttackLight = true;
	UE_LOG(LogTemp, Warning, TEXT("attacking"));
	bPressedAttackLight = false;
}

void AOnnaBugeishaCharacter::AttackHeavy()
{
	bPressedAttackHeavy = true;
	
		UE_LOG(LogTemp, Warning, TEXT("Heavy attack charging"));
	
}

void AOnnaBugeishaCharacter::AttackHeavyStop()
{
	UE_LOG(LogTemp, Warning, TEXT("Heavy charge attack"));

	bPressedAttackHeavy = false;
}
void AOnnaBugeishaCharacter::Guard()
{
	DamageMulitplier = UneffectedDamageMultiplier * .15;
	UE_LOG(LogTemp, Warning, TEXT("Guarding damage %f"), DamageMulitplier);
}
void AOnnaBugeishaCharacter::GuardStop()
{
	DamageMulitplier = UneffectedDamageMultiplier;
	UE_LOG(LogTemp, Warning, TEXT("GuardingStopped, damage now %f"), DamageMulitplier);
	

}
void AOnnaBugeishaCharacter::Roll()
{

	UE_LOG(LogTemp, Warning, TEXT("Roll supposedly"));
}

void AOnnaBugeishaCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintMultiplier;
	UE_LOG(LogTemp, Warning, TEXT("Sprint started"));
}

void AOnnaBugeishaCharacter::SprintStop()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintMultiplier;
	UE_LOG(LogTemp, Warning, TEXT("Sprint Stopped"));
}


void AOnnaBugeishaCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AOnnaBugeishaCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AOnnaBugeishaCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AOnnaBugeishaCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AOnnaBugeishaCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AOnnaBugeishaCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AOnnaBugeishaCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

// Called every frame
void AOnnaBugeishaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPressedAttackHeavy == true|| bPressedAttackLight == true) {
		LineTraceDebugLine();
	 }

}

void AOnnaBugeishaCharacter::LineTraceDebugLine()
{
	DrawDebugLine(
		GetWorld(),
		GetActorLocation(),
		FVector (GetActorLocation() + GetActorRotation().Vector()* 100),
		FColor(255, 0, 0),
		false,
		0.5f,
		0.1f
		);
}


