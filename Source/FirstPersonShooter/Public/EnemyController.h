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

	UPROPERTY(EditAnywhere, Category = "Character_BP") 
	TSubclassOf<class AFirstPersonShooterCharacter>
	CharacterBlueprint;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootBox;

	UPROPERTY(EditAnywhere)
		float Speed = 100.0f;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	FVector Direction;

	//depricated
	//float playerHealth = 100.0f;
	//float damage = 10.0f;
	//float minHealth = 10.0f;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
