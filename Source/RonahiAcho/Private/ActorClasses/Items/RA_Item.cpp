// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorClasses/Items/RA_Item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CharacterClasses/RA_AchoCharacter.h"

#include "RonahiAcho/DebugMacros.h"

ARA_Item::ARA_Item()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	//Create StaticMeshComponent for Item.
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMesh;

	//Create Sphere for on component begin overlap
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(StaticMesh);


}


void ARA_Item::BeginPlay()
{
	Super::BeginPlay();

	//// When Sphere Overlaps or EndOverlaps, OnSphereOverlap and EndSphereOverlap function should work.
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ARA_Item::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ARA_Item::EndSphereOverlap);
}


void ARA_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARA_Item::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//When AchoCharacter Overlap with sphere component ,setting Overlaping item.
	ARA_AchoCharacter* AchoCharacter = Cast<ARA_AchoCharacter>(OtherActor);
	if (AchoCharacter)
	{
		AchoCharacter->SetOverlapingItem(this);
	}

}

void ARA_Item::EndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	//When AchoCharacter Endoverlap with sphere component ,setting Overlaping item nullptr.
	ARA_AchoCharacter* AchoCharacter = Cast<ARA_AchoCharacter>(OtherActor);
	if (AchoCharacter)
	{
		AchoCharacter->SetOverlapingItem(nullptr);
	}
}



