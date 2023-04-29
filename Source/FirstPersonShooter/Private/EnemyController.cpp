// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

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

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay(); //super = parent, so in this case the Actor
	
}

// Called every frame
void AEnemyController::Tick(float DeltaTime) //like Update()
{
	Super::Tick(DeltaTime);

	FVector enemyLocation = GetActorLocation();

	//X left right, Y forward back, Z up down
	enemyLocation.X += Direction.X * Speed * DeltaTime;
	enemyLocation.Y += Direction.Y * Speed * DeltaTime; //without speed * time, they will move very slowly
	//time is so that it looks the same on any machine, do this whenever working with movement

	SetActorLocation(enemyLocation); //moving the enemy in the above direction, to enemyLocation, to chase player
}

void AEnemyController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* collidedWith = (ACharacter*)OtherActor;

	if (collidedWith == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

