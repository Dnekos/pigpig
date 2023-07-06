// Fill out your copyright notice in the Description page of Project Settings.


#include "Storage.h"

// Sets default values
AStorage::AStorage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AStorage::BeginPlay()
{
	Super::BeginPlay();

	mValue = NewObject<UInfPrecisionFloat>();
}

bool AStorage::AddLargeFloat(ULargeFloat* largeFloat)
{
	mValue->Add(largeFloat);
	return true;
}

bool CanSubtractFrom(UInfPrecisionFloat* ipf, ULargeFloat* lf)
{
	FString ipfStr = ipf->ToString();
	FString lfStr = FString::Printf(TEXT("%f"),lf->mValue);
	lfStr = lfStr.Replace(TEXT("."), TEXT(""));

	int ipfLen = ipfStr.Len();
	int lfLen = lfStr.Len();

	if(ipfLen > lfLen) return true;
	if(ipfLen < lfLen) return false;

	for(int i = 0; i < ipfLen; i++)
	{
		if(ipfStr[i] > lfStr[i]) return true;
		if(ipfStr[i] < lfStr[i]) return false;
	}

	return true; // they are equal
}

bool AStorage::SubtractLargeFloat(ULargeFloat* largeFloat)
{
	if(!CanSubtractFrom(mValue, largeFloat)) return false;

	mValue->Subtract(largeFloat);
	return true;
}