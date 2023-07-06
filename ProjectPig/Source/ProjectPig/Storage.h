// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InfPrecisionFloat.h"
#include "GameFramework/Actor.h"
#include "Storage.generated.h"

UCLASS()
class PROJECTPIG_API AStorage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStorage();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Value", Keywords = "get value large float"))
		void SetValue(UInfPrecisionFloat* value) { mValue = value; }

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get Value", Keywords = "set value large float"))
		UInfPrecisionFloat* GetValue() { return mValue; }

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Large Float", Keywords = "add large float"))
		bool AddLargeFloat(ULargeFloat* largeFloat);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Subtract Large Float", Keywords = "subtract large float"))
		bool SubtractLargeFloat(ULargeFloat* largeFloat);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UInfPrecisionFloat* mValue;
};
