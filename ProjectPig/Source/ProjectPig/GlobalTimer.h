// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlobalTimer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGlobalTimerDelegate);

UCLASS()
class PROJECTPIG_API AGlobalTimer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlobalTimer();

	UPROPERTY()
		TArray<FGlobalTimerDelegate> OnGenerateCall;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get Global Timer", Keywords = "get global timer"))
		static AGlobalTimer* GetGlobalTimer() { return AGlobalTimer::smInstance; }

		FGlobalTimerDelegate& GetDelegate();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	int mDeleCallCounter = 0;

	UPROPERTY()
	int mDeleSetCounter = 0;

private :
	static AGlobalTimer* smInstance;
	FTimerHandle mTimerHandle;

	// delegate calls
	void CallGenerationEvent();

};
