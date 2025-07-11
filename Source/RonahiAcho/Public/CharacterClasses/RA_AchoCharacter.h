// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "RA_AchoCharacter.generated.h"


class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class UGroomComponent;
class ARA_Item;
class UAnimMontage;



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

	/** InputMappingContex */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* AchoInputMappingContex;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* AchoFighting_IMC;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MovementAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EquipAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AttackAction;

	/** Called for movement input */
	void AchoMovement(const FInputActionValue& Value);

	/** Called for looking input */
	void AchoLook(const FInputActionValue& Value);

	/** Called for Equip E input */
	void EKeyPressed(const FInputActionValue& Value);

	/** Called for AttackAction input */
	void RightMousePressed(const FInputActionValue& Value);

	//GroomComponent Variable
	UPROPERTY(VisibleAnywhere, Category = "GroomAsset")
	UGroomComponent* AchoHair;

	UPROPERTY(VisibleAnywhere, Category = "GroomAsset")
	UGroomComponent* AchoAyebrows;


private:

	ECharacterState CharacterState = ECharacterState::ECS_UnEquiped;
	/*
	Animation Montage 
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;


	
	UPROPERTY(VisibleInstanceOnly)
	ARA_Item* OverlapingItem;

public:

	FORCEINLINE void SetOverlapingItem(ARA_Item* Item) { OverlapingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }

};
