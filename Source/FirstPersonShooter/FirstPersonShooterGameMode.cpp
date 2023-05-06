// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstPersonShooterGameMode.h"
#include "FirstPersonShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "Kismet/GameplayStatics.h"
#include "EnemyController.h" //needed to spawn the blueprint which inherits from EnemyController

#include "GameWidget.h" //needed to cast the StartingWidget to our custom widget class

//cpp is where you define all the methods

AFirstPersonShooterGameMode::AFirstPersonShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PrimaryActorTick.bCanEverTick = true; //tick functionality will not work without this line

}

void AFirstPersonShooterGameMode::Tick(float DeltaTime) //this is all to do with spawning enemies
{
	Super::Tick(DeltaTime); //the super line has to be the first line

	EnemyTimer -= DeltaTime; //delta time so game runs at same speed regardless of cpu spec/fps

	if (EnemyTimer < 0.0f)
	{
		EnemyTimer = SpawnRate;

		UWorld* world = GetWorld(); //UWorld is like the scene or level

		if (world) //if variable world is true, so if it's not null
		{
			int playerIndex = 0;
			FVector playerLocation = UGameplayStatics::GetPlayerCharacter(world, playerIndex)
				->GetActorLocation(); //FVector is like Vector3

			FVector enemyLocation = playerLocation; //starts off at exact player location

			float randomDistance = FMath::RandRange(100.0f, 1000.0f);

			//X left right, Y forward back, Z up down in Unreal
			enemyLocation.X += randomDistance;
			enemyLocation.Y += randomDistance;

			//this is like instantiate in Unity
			AEnemyController* enemy = world->SpawnActor<AEnemyController>(EnemyBlueprint, 
				enemyLocation, FRotator::ZeroRotator);

			//minus to get the difference
			if (enemy != nullptr)
				enemy->Direction = (playerLocation - enemyLocation).GetSafeNormal(); //to make an arrow towards player, size 1, like normalized
		}
	}

}

void AFirstPersonShooterGameMode::BeginPlay()
{
	Super::BeginPlay(); //super calling from it's parent class which in this case is AGameModeBase

	ChangeMenuWidget(StartingWidgetClass);

	//cast it as UGameWidget, our custom child of UserWidget
	((UGameWidget*)CurrentWidget)->Load();
}

void AFirstPersonShooterGameMode::IncreaseScore()
{
	Score += 1; //score equals score plus 1 shorthand

	((UGameWidget*)CurrentWidget)->SetScore(Score);
}

void AFirstPersonShooterGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget>NewWidgetClass)
{
	//we call ChangeMenuWidget whenever we want to remove the ScoreText and replace it
	if (CurrentWidget != nullptr) //if the widget in the game (with the score text) now is not null
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr; //remove it from view then make it null

	}

	if (NewWidgetClass != nullptr) //if it's not null we need to create a new widget and add it to the viewport
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

		if (CurrentWidget != nullptr) //only if this switchover was successful
		{
			CurrentWidget->AddToViewport();
		}

	}

}

void AFirstPersonShooterGameMode::OnGameOver()
{
	((UGameWidget*)CurrentWidget)->OnGameOver(Score);
}



