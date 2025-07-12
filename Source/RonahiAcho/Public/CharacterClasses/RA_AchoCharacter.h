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
class ARA_Weapon;



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




protected:

	/** 
	*  InputMappingContex
	**/
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* AchoInputMappingContex;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* AchoFighting_IMC;

	/** 
	*  Acho Input Action
	**/
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EquipAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AttackAction;

	/**
	*  Play Montage Function
	**/
	void PlayAttackMontages();
	bool CanAttack();
	bool bCanDisarm();
	bool bCanArm();
	void PlayEquipMontage(FName SectionName);

	UFUNCTION(BlueprintCallable)
	void EndAttack();

	UFUNCTION(BlueprintCallable)
	void DisArm();

	UFUNCTION(BlueprintCallable)
	void Arm();

	UFUNCTION(BlueprintCallable)
	void FinishEquipment();



	/** 
	*  Callback function for input
	**/
	void AchoMovement(const FInputActionValue& Value);
	void AchoLook(const FInputActionValue& Value);
	void EKeyPressed(const FInputActionValue& Value);
	void RightMousePressed(const FInputActionValue& Value);



protected:

	/**
	*  GroomComponent Variables
	**/
	UPROPERTY(VisibleAnywhere, Category = "GroomAsset")
	UGroomComponent* AchoHair;

	UPROPERTY(VisibleAnywhere, Category = "GroomAsset")
	UGroomComponent* AchoAyebrows;





private:

	ECharacterState CharacterState = ECharacterState::ECS_UnEquiped;
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	ARA_Weapon* EquipedWeapon;

	/*
	Animation Montage 
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;
	


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
