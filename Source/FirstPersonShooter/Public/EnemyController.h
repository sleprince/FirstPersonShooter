// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyController.generated.h"

UCLASS() //all created classes have A at the start
class FIRSTPERSONSHOOTER_API AEnemyController : public AActor
{
	GENERATED_BODY()

		//the final 2 methods are similar to Start() and Update() in C#
	
public:	
	// Sets default values for this actor's properties
	AEnemyController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
