// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

//always has to be at the end
#include "GameWidget.generated.h"


/**
 * 
 */
UCLASS()
class FIRSTPERSONSHOOTER_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void Load();

	void SetScore(int score);

	UPROPERTY() //the asterisk after means it's a pointer
		UTextBlock* ScoreText;

	UFUNCTION(BlueprintCallable, Category = "GameOver")
	void OnGameOver(int score);
	
};
