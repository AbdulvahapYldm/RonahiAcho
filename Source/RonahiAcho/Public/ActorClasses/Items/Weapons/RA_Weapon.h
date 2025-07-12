// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorClasses/Items/RA_Item.h"
#include "RA_Weapon.generated.h"

/**
 * 
 */
UCLASS()
class RONAHIACHO_API ARA_Weapon : public ARA_Item
{
	GENERATED_BODY()

public:

	void Equip(USceneComponent* InParent, FName SocketName);

	void AttachMeshToSocket(USceneComponent* InParent, const FName& SocketName);

protected:

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void EndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
};
