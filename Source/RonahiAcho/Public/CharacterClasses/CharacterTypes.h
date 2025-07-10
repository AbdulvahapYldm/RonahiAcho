#pragma once




UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_UnEquiped UMETA(DisplayName = "UnEquiped"),
	ECS_EquipWeapon UMETA(DisplayName = "EquipWeapon")
};