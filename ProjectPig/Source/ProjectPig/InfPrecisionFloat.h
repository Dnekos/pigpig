// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LargeFloat.h"
#include "UObject/NoExportTypes.h"
#include "InfPrecisionFloat.generated.h"

USTRUCT()
struct FUInt4
{
	GENERATED_BODY()

	bool x[4];

	FUInt4()
	{
		for(int i = 0; i < 4; i++)
			x[i] = false;
	}

	FUInt4(int n)
	{
		for(int i = 0; i < 4; i++)
			x[i] = (n & (1 << i)) != 0;
	}

	void operator=(const int n)
	{
		for(int i = 0; i < 4; i++)
			x[i] = (n & (1 << i)) != 0;
	}

	operator int() const
	{
		int n = 0;
		for(int i = 0; i < 4; i++)
			n += x[i] ? 1 << i : 0;

		return n;
	}

};

UCLASS(BlueprintType, Blueprintable)
class PROJECTPIG_API UInfPrecisionFloat : public UObject
{
	GENERATED_BODY()

public:
	UInfPrecisionFloat();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "InfPrecisionFloat + LargeFloat", CompactNodeTitle = "+", Keywords = "+ add"), Category = "Math|InfPrecisionFloat")
	UInfPrecisionFloat* Add(const ULargeFloat* rhs);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "InfPrecisionFloat - LargeFloat", CompactNodeTitle = "-", Keywords = "- subtract"), Category = "Math|InfPrecisionFloat")
	UInfPrecisionFloat* Subtract(const ULargeFloat* rhs);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "To String", Keywords = "to string inf infinite precision float"))
	FString ToString();
	
private:
	UPROPERTY(EditAnywhere, Category = "InfPrecisionFloat Values")
	TArray<FUInt4> mDigits;
};
