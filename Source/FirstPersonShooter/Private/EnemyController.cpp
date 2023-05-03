// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; //so can turn this off if no update functionality

	//rootbox is needed for the invisible box outline in editor
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

	RootBox->SetGenerateOverlapEvents(true);

	RootBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyController::OnOverlap);

	//get the ghost mesh
	//RootBox->GetDefaultSubobjectByName("StaticMesh");

}

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
	


	//SetActorLocation(enemyLocation); 
}

//like OnCollisionEnter
void AEnemyController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* collidedWith = (ACharacter*)OtherActor;

	if (collidedWith == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		// Access the Health variable in the other actor's blueprint
		//if (ACharacter* Other = Cast<CharacterBlueprint>(OtherActor))
		//{
		//	Other->Health -= 0; // assuming that Health is a float variable in AMyOtherActor
		//}
		//UGameplayStatics::SetGamePaused(GetWorld(), true);

		//CharacterBlueprint-
	}
	else if (OtherActor->GetName().Contains("Projectile")) //only runs if the above is false and this is true
	{
		//OtherActor->Destroy();
		//this->Destroy();
	}
}

