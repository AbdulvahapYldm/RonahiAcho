// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RA_AchoCharacter.generated.h"

UCLASS()
class RONAHIACHO_API ARA_AchoCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ARA_AchoCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:

	virtual void BeginPlay() override;





};
