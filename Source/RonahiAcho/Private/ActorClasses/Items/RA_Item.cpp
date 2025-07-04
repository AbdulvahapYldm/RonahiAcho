// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorClasses/Items/RA_Item.h"
#include "Components/StaticMeshComponent.h"
#include "RonahiAcho/DebugMacros.h"

ARA_Item::ARA_Item()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	//Create StaticMeshComponent for Item.
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMesh;


}


void ARA_Item::BeginPlay()
{
	Super::BeginPlay();

}


void ARA_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

