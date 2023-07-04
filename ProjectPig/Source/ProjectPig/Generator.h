// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LargeFloat.h"
#include "Storage.h"
#include "GlobalTimer.h"
#include "Misc/DateTime.h"
#include "GameFramework/Actor.h"
#include "Generator.generated.h"

UCLASS(Blueprintable)
class PROJECTPIG_API AGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerator();

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Generate", Keywords = "generate resource"))
		// Generates amount of materials per second
		ULargeFloat* Generate(); // based on resource per second


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Target Storage", Keywords = "set target storage"))
		void SetTargetStorage(AStorage* storage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 
	UFUNCTION()
	void DoGenerate();

	FGlobalTimerDelegate* mCurrentDelegate;

	AStorage* mTargetStorage;

	float mLastGenerated;
};
