// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator.h"

// Sets default values
AGenerator::AGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// mLastGenerated = FDateTime::UtcNow().;
}

// Called when the game starts or when spawned
void AGenerator::BeginPlay()
{
	Super::BeginPlay();

	AGlobalTimer::GetGlobalTimer()->OnTenthSecond.AddDynamic(this, &AGenerator::DoGenerate);
}

ULargeFloat* AGenerator::Generate_Implementation()
{
	ULargeFloat* res = NewObject<ULargeFloat>();
	return res;
}

void AGenerator::DoGenerate()
{
	if(!mTargetStorage)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::
			Red, TEXT("ERROR: mTargetStorage is not set."));
		return;
	}

	ULargeFloat* v = Generate();

	UInfPrecisionFloat* storageValue = mTargetStorage->GetValue();

	// add to storage
	storageValue->Add(v);
}

void AGenerator::SetTargetStorage(AStorage* storage)
{
	mTargetStorage = storage;
}