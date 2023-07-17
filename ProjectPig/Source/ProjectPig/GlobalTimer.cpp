// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalTimer.h"

AGlobalTimer* AGlobalTimer::smInstance = nullptr;

// Sets default values
AGlobalTimer::AGlobalTimer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	smInstance = this;

	// add 10 delegates to delegate array
	for(int i = 0; i < 10; i++)
		OnGenerateCall.Add(FGlobalTimerDelegate());
}

// Called when the game starts or when spawned
void AGlobalTimer::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(mTimerHandle, this, &AGlobalTimer::CallGenerationEvent, 0.1, true, 0);
}

// Called every frame
void AGlobalTimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FGlobalTimerDelegate& AGlobalTimer::GetDelegate()
{
	int i = mDeleSetCounter;
	mDeleSetCounter = (mDeleSetCounter + 1) % 10; // looping increment
	return OnGenerateCall[i];
}

void AGlobalTimer::CallGenerationEvent()
{
	OnGenerateCall[mDeleCallCounter].Broadcast();
	mDeleCallCounter = (mDeleCallCounter + 1) % 10; // looping increment
}

