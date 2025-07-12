// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorClasses/Items/Weapons/RA_Weapon.h"
#include "CharacterClasses/RA_AchoCharacter.h"






void ARA_Weapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ARA_Weapon::EndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::EndSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}



void ARA_Weapon::Equip(USceneComponent* InParent, FName SocketName)
{
	AttachMeshToSocket(InParent, SocketName);
	
}

void ARA_Weapon::AttachMeshToSocket(USceneComponent* InParent, const FName& SocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	StaticMesh->AttachToComponent(InParent, TransformRules, SocketName);
}
