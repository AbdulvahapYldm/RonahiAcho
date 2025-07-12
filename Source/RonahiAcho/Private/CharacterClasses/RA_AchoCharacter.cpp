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
#include "ActorClasses/Items/RA_Item.h"
#include "ActorClasses/Items/Weapons/RA_Weapon.h"
#include "Animation/AnimMontage.h"





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
			Subsystem->AddMappingContext(AchoFighting_IMC, 0);
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
	// Set up action bindings for input
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ARA_AchoCharacter::AchoMovement);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARA_AchoCharacter::AchoLook);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Started, this, &ARA_AchoCharacter::EKeyPressed);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ARA_AchoCharacter::RightMousePressed);
		
	}

}

void ARA_AchoCharacter::AchoMovement(const FInputActionValue& Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	
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




void ARA_AchoCharacter::EKeyPressed(const FInputActionValue& Value)
{ 
	
	ARA_Weapon* OverlapingWeapon = Cast<ARA_Weapon>(OverlapingItem);
	if (OverlapingWeapon)
	{
		OverlapingWeapon->Equip(GetMesh(),FName("RightHandSocket"));
		CharacterState = ECharacterState::ECS_EquipWeapon;
		OverlapingItem = nullptr;
		EquipedWeapon = OverlapingWeapon;
		
	}
	else
	{
		if (bCanDisarm())
		{
			PlayEquipMontage(FName("UnEquip"));
			CharacterState = ECharacterState::ECS_UnEquiped;
			ActionState = EActionState::EAS_EquipingWeapon;
		}
		else if (bCanArm()) 
		{
			PlayEquipMontage(FName("Equip"));
			CharacterState = ECharacterState::ECS_EquipWeapon;
			ActionState = EActionState::EAS_EquipingWeapon;
		}
	}

}




void ARA_AchoCharacter::RightMousePressed(const FInputActionValue& Value)
{

	if (CanAttack())
	{
		PlayAttackMontages();
		ActionState = EActionState::EAS_Attacking;
	}
	

}

void ARA_AchoCharacter::PlayAttackMontages()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		const int32 AttackTypeSelection = FMath::RandRange(0, 1);
		FName SectionName = FName();

		switch (AttackTypeSelection)
		{

		case 0:
			SectionName = FName("Attack_01");
			break;
		case 1:
			SectionName = FName("Attack_02");
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}
void ARA_AchoCharacter::PlayEquipMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
}

bool ARA_AchoCharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_UnEquiped;
}

void ARA_AchoCharacter::EndAttack()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ARA_AchoCharacter::DisArm()
{
	if (EquipedWeapon)
	{
		EquipedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
	}
}

void ARA_AchoCharacter::Arm()
{
	if (EquipedWeapon)
	{
		EquipedWeapon->AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));
	}
}

void ARA_AchoCharacter::FinishEquipment()
{
	ActionState = EActionState::EAS_Unoccupied;
}

bool ARA_AchoCharacter::bCanDisarm()
{
	return ActionState == EActionState::EAS_Unoccupied && 
		CharacterState != ECharacterState::ECS_UnEquiped ;
}

bool ARA_AchoCharacter::bCanArm()
{
	return ActionState == EActionState::EAS_Unoccupied&& 
		CharacterState == ECharacterState::ECS_UnEquiped&& EquipedWeapon;
}
