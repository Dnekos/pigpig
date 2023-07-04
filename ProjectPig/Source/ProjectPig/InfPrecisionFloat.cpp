// Fill out your copyright notice in the Description page of Project Settings.


#include "InfPrecisionFloat.h"


UInfPrecisionFloat::UInfPrecisionFloat()
{
	// UInfPrecisionFloat reserves a kb of memory (4 bytes * 250)
	mDigits.Init(0, 250);
}

UInfPrecisionFloat* UInfPrecisionFloat::Add(const ULargeFloat* rhs)
{
	// stack
	TArray<int> stack;

	float v = rhs->mValue, e = rhs->mExponent;
	// loop through
	while(v != 0)
	{
		int digit = (int)floor(v) % 10;
		v -= digit;
		v *= 10;
		stack.Add(digit);
		e--;
	}

	for(int i = 0; i < e; i++)
		stack.Add(0);
	
	// setup stack variables
	int idx = stack.Num() - rhs->mExponent;
	int carry = 0;
	int holder = 0;

	while(stack.Num() > 0 || carry != 0)
	{
		holder = carry + ((stack.Num() > 0) ? stack.Pop() : 0) + mDigits[idx];
		carry = 0;

		if(holder > 9)
		{
			carry = 1;
			holder -= 10;
		}

		mDigits[idx] = holder;
		idx++;
	}

	return this;
}

FString UInfPrecisionFloat::ToString()
{
	FString str;

	{
		UE_LOG(LogTemp, Warning, TEXT("=========================== UInfPrecisionFloat ==========================="));
	}

	int idx = 0;
	int lastNonZero = 0;
	for(const FUInt4& d : mDigits)
	{
		{
			UE_LOG(LogTemp, Warning, TEXT("{ %d | %s %s %s %s } "), (int)d, d.x[0] ? TEXT("True") : TEXT("False"), d.x[1] ? TEXT("True") : TEXT("False"), d.x[2] ? TEXT("True") : TEXT("False"), d.x[3] ? TEXT("True") : TEXT("False"));
		}

		if((int)d != 0)
			lastNonZero = idx;

		str.Append(FString::Printf(TEXT("%d"), (int)d));
		idx++;
	}

	str.RemoveAt(lastNonZero + 1, str.Len() - lastNonZero);

	str = str.Reverse();

	return str;
}