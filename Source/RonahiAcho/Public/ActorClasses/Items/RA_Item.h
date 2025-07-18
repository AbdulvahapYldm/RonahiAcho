// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RA_Item.generated.h"


class USphereComponent;

UCLASS()
class RONAHIACHO_API ARA_Item : public AActor
{
	GENERATED_BODY()
	
public:	

	ARA_Item();
	virtual void Tick(float DeltaTime) override;
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;




private:

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;


};
