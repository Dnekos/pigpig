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

	UPROPERTY(BlueprintAssignable, Category = "Timer Delegate")
		FGlobalTimerDelegate OnTenthSecond;

	UPROPERTY(BlueprintAssignable, Category = "Timer Delegate")
		FGlobalTimerDelegate OnOneSecond;

	UPROPERTY(BlueprintAssignable, Category = "Timer Delegate")
		FGlobalTimerDelegate OnTenSeconds;

	UPROPERTY(BlueprintAssignable, Category = "Timer Delegate")
		FGlobalTimerDelegate OnHundredSeconds;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get Global Timer", Keywords = "get global timer"))
		static AGlobalTimer* GetGlobalTimer() { return AGlobalTimer::smInstance; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private :
	static AGlobalTimer* smInstance;
	FTimerHandle mTimerHandle;

	int mTenths = 0;
	int mOnes = 0;
	int mTens = 0;

	// delegate calls
	void CallTenthSecond();
	void CallOneSecond();
	void CallTenSeconds();
	void CallHundredSeconds();

};
