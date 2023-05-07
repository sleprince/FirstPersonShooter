// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

//#include "MyGameModeBase.h"
#include "FirstPersonShooter/FirstPersonShooterGameMode.h" //finally figured it out, had to put FirstPersonShooter/ in front
#include "GameWidget.h"

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; //so can turn this off if no update functionality

	//rootbox is needed for the invisible box outline in editor
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

	RootBox->SetGenerateOverlapEvents(true);

	RootBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyController::OnOverlap);

}

//Any class that inherits from Actor has A prefix.

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay(); //super = parent, so in this case the Actor
	
	int lifespanInSeconds = 10;

	this->SetLifeSpan(lifespanInSeconds);
}

// Called every frame
void AEnemyController::Tick(float DeltaTime) //like Update()
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (PlayerPawn)
	{
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		FVector EnemyLocation = GetActorLocation();
		FVector Dir = (PlayerLocation - EnemyLocation).GetSafeNormal();

		//without speed * time, they will move very slowly
		//time is so that it looks the same on any machine, do this whenever working with movement
		//moving the enemy in the above direction, to enemyLocation, to chase player
		SetActorLocation(EnemyLocation + Dir * Speed * DeltaTime);
	}
	


	//SetActorLocation(enemyLocation); //this version did not update, they kept going to player's old position
}

//like OnCollisionEnter
void AEnemyController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* collidedWith = (ACharacter*)OtherActor;

	if (collidedWith == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{

		playerHealth -= damage;

		if (playerHealth < minHealth)
		{
			//cast as an fpsGameMode, * is cast as
			((AFirstPersonShooterGameMode*)GetWorld()->GetAuthGameMode())
				->OnGameOver();  //grabbing the custom gamemode set in the game //run game over function

			UGameplayStatics::SetGamePaused(GetWorld(), true); //pause game
		}
		
	}
	else if (OtherActor->GetName().Contains("Projectile")) //only runs if the above is false and this is true
	{
		//depricated
		
		//OtherActor->Destroy();
		//this->Destroy();

		//cast as an fpsGameMode, * is cast as
		//((AFirstPersonShooterGameMode*)GetWorld()->GetAuthGameMode())
		//->IncreaseScore();  //grabbing the custom gamemode set in the game
	}
}

