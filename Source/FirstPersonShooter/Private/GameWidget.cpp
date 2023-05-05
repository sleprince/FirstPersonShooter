// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"

//starts with U instead of A because it is a user interface
void UGameWidget::Load()
{
	//used for getting the variable we just made in Unreal Editor within the Blueprint that's based on this class
	//const makes it read only, FName is a lightweight string
	const FName TextBlockName = FName(TEXT("ScoreTextBlock"));

	if (ScoreText == nullptr) //if it is a null pointer. = assigning a value, == checking a value
	{
		//if it's null this will grab the relevant variable from Blueprint
		ScoreText = (UTextBlock*)(WidgetTree->FindWidget(TextBlockName)); 
	}
}

void UGameWidget::SetScore(int score)
{
	// ->is for pointers to a class instance

	//	.is for class instances

	//	::is for classnames - for example when using a static member

	if (ScoreText != nullptr) //we can't set a score unless ScoreText is not null
	{
		//F means formatted
		ScoreText->SetText(FText::FromString(FString(TEXT("Score: "))
		+ FString::FromInt(score))); //like .ToString()

	}
}