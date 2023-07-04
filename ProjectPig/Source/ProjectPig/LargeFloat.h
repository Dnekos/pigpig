#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LargeFloat.generated.h"

UCLASS(BlueprintType, Blueprintable)
class PROJECTPIG_API ULargeFloat : public UObject
{
public:
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LargeFloat Values")
		float mValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LargeFloat Values")
		int32 mExponent;

	// Sets default values for this empty's properties
	ULargeFloat();

	// Blueprint Constructor
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Make LargeFloat", Keywords = "make large float"))
		static ULargeFloat* makeLargeFloat(float value, int exponent);

	// Blueprint Operator Overloads
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "LargeFloat + LargeFloat", CompactNodeTitle = "+", Keywords = "+ add"), Category = "Math|LargeFLoat")
		ULargeFloat* add(const ULargeFloat* rhs) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "LargeFloat - LargeFloat", CompactNodeTitle = "-", Keywords = "- subtract"), Category = "Math|LargeFLoat")
		ULargeFloat* subtract(const ULargeFloat* rhs) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "LargeFloat * LargeFloat", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "Math|LargeFLoat")
		ULargeFloat* multiply(const ULargeFloat* rhs) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "LargeFloat / LargeFloat", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "Math|LargeFLoat")
		ULargeFloat* divide(const ULargeFloat* rhs) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "LargeFloat > LargeFloat", CompactNodeTitle = ">", Keywords = "> greater than"), Category = "Math|LargeFLoat")
		bool greaterThan(const ULargeFloat* rhs) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "LargeFloat < LargeFloat", CompactNodeTitle = "<", Keywords = "< less than"), Category = "Math|LargeFLoat")
		bool lessThan(const ULargeFloat* rhs) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "LargeFloat = LargeFloat", CompactNodeTitle = "=", Keywords = "= equal to"), Category = "Math|LargeFLoat")
		bool equalTo(const ULargeFloat* rhs) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "LargeFloat != LargeFloat", CompactNodeTitle = "!=", Keywords = "!= not equal to"), Category = "Math|LargeFLoat")
		bool notEqualTo(const ULargeFloat* rhs) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "LargeFloat >= LargeFloat", CompactNodeTitle = ">=", Keywords = ">= greater than equal to"), Category = "Math|LargeFLoat")
		bool greaterThanEqualTo(const ULargeFloat* rhs) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "LargeFloat <= LargeFloat", CompactNodeTitle = "<=", Keywords = "<= less than equal to"), Category = "Math|LargeFLoat")
		bool lessThanEqualTo(const ULargeFloat* rhs) const;

	// To String
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "To Scientific", Keywords = "string text scientific"))
		FString toScientificNotation();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "To Postfix", Keywords = "string text postfix"))
		FString toPostfixNotation();

private:
	void cleanValue();

	const static size_t csmLimit = 52;
	const static int csmPrecision = 10;
	static FString csmPostfix[csmLimit];
};