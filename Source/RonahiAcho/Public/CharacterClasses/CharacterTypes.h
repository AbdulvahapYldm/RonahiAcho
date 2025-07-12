#pragma once




UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_UnEquiped UMETA(DisplayName = "UnEquiped"),
	ECS_EquipWeapon UMETA(DisplayName = "EquipWeapon")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	EAS_EquipingWeapon UMETA(DisplayName = "EquipingWeapon")
};