// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalTimer.h"

AGlobalTimer* AGlobalTimer::smInstance = nullptr;

// Sets default values
AGlobalTimer::AGlobalTimer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	smInstance = this;
}

// Called when the game starts or when spawned
void AGlobalTimer::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(mTimerHandle, this, &AGlobalTimer::CallTenthSecond, 0.1, true, 0);
}

// Called every frame
void AGlobalTimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGlobalTimer::CallTenthSecond()
{
	mTenths++;
	OnTenthSecond.Broadcast();

	if(mTenths % 10 == 0)
	{
		CallOneSecond();
		mTenths = 0;
	}
}

void AGlobalTimer::CallOneSecond()
{
	mOnes++;
	OnOneSecond.Broadcast();

	if(mOnes % 10 == 0)
	{
		CallTenSeconds();
		mOnes = 0;
	}
}

void AGlobalTimer::CallTenSeconds()
{
	mTens++;
	OnTenSeconds.Broadcast();

	if(mTens % 10 == 0)
	{
		CallHundredSeconds();
		mTens = 0;
	}
}

void AGlobalTimer::CallHundredSeconds()
{
	OnHundredSeconds.Broadcast();
}

