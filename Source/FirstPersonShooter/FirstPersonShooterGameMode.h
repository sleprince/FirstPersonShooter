// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Blueprint/UserWidget.h" //needed to do TSubclassOf<UUserWidget>

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
	float SpawnRate = 2.0f;

	// Called every frame
	virtual void Tick(float DeltaTime) override; //virtual because not implemented in this file
	//override because we are going to override it in cpp file

	virtual void BeginPlay() override; //like onStart()

	void IncreaseScore();

	//UMG is Unreal Motion Graphics UI Designer
	UFUNCTION(BlueprintCallable, Category = "UMG Game") //so we can use this in Unreal
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected: //accessible inside this class and inside any children

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	int Score;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game") //so we can use this in Editor
		TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
		UUserWidget* CurrentWidget;

};



