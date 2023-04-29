// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FirstPersonShooterGameMode.generated.h"

//header is where you declare all variables and functions

UCLASS(minimalapi)
class AFirstPersonShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFirstPersonShooterGameMode();

	//public to be accessed by Unreal
	//enemies as blueprints so that we can have many, like with prefabs

	UPROPERTY(EditAnywhere, Category = "Spawn") //editanywhere is like serializefield kind of, category like tag
		TSubclassOf<class AEnemyController> //blueprint will be a subclass of EnemyController, T for template
			EnemyBlueprint;

	float EnemyTimer; //pause between each new enemy spawning
	float SpawnRate = 5.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override; //virtual because not implemented in this file
	//override because we are going to override it in cpp file

	virtual void BeginPlay() override; //like onStart()

};



