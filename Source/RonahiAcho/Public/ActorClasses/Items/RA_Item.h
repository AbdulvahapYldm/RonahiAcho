// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RA_Item.generated.h"

UCLASS()
class RONAHIACHO_API ARA_Item : public AActor
{
	GENERATED_BODY()
	
public:	

	ARA_Item();
	virtual void Tick(float DeltaTime) override;
protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

};
