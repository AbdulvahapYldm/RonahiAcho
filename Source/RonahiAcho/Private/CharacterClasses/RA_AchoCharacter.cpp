// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterClasses/RA_AchoCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


ARA_AchoCharacter::ARA_AchoCharacter()
{
 
	PrimaryActorTick.bCanEverTick = true;

	//Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraBoom->SetupAttachment(GetRootComponent());
	//Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(CameraBoom);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);


	//Create GroomComponent and attached mesh componnet
	AchoHair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	AchoHair->SetupAttachment(GetMesh());
	AchoHair->AttachmentName = FString("head");

	AchoAyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	AchoAyebrows->SetupAttachment(GetMesh());
	AchoAyebrows->AttachmentName = FString("head");

}


void ARA_AchoCharacter::BeginPlay()
{
	Super::BeginPlay();

	//EnhancedInputSystem
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(AchoInputMappingContex, 0);
		}
	}
}


void ARA_AchoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ARA_AchoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {


		// Moving
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ARA_AchoCharacter::AchoMovement);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARA_AchoCharacter::AchoLook);

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	}

}

void ARA_AchoCharacter::AchoMovement(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementValue = Value.Get<FVector2D>();

	// Find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// Get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// Get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Add movement 
	AddMovementInput(ForwardDirection, MovementValue.Y);
	AddMovementInput(RightDirection, MovementValue.X);
}

void ARA_AchoCharacter::AchoLook(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	// add yaw and pitch input to controller
	AddControllerPitchInput(LookAxisValue.Y);
	AddControllerYawInput(LookAxisValue.X);
}
