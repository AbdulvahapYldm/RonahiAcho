// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceClasses/RA_AnimInstance.h"
#include "CharacterClasses/RA_AchoCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void URA_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	AchoCharacter = Cast<ARA_AchoCharacter>(TryGetPawnOwner());

	if (AchoCharacter)
	{
		AchoCharacterMovement = AchoCharacter->GetCharacterMovement();
	}
}

void URA_AnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (AchoCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(AchoCharacterMovement->Velocity);
		IsFalling = AchoCharacterMovement->IsFalling();
		CharacterState = AchoCharacter->GetCharacterState();
	}
}
