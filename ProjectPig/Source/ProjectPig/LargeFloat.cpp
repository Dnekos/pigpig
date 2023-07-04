#include "LargeFloat.h"

FString ULargeFloat::csmPostfix[csmLimit] = { "",
"Thousand", "Million", "Billion", "Trillion",
"Quadrillion", "Quintillion", "Sextillion", "Septillion",
"Octillion" , "Nonillion" , "Decillion" , "Undecillion",
"Duodecillion" , "Tredecillion" , "Quattuordecillion" , "Quindecillion" ,
"Sexdecillion" , "Septendecillion" , "Octodecillion" , "Novemdecillion",
"Vigintillion" , "Unvigintillion" , "Duovigintillion" , "Trevigintillion",
"Quattuorvigintillion" , "Quinvigintillion" , "Sexvigintillion" , "Septenvigintillion" ,
"Octovigintillion" , "Novemvigintillion" , "Trigintillion" , "Untrigintillion" ,
"Duotrigintillion" , "Tretrigintillion" , "Quarttourtrigintillion" , "Quintrigintillion" ,
"Sextrigintillion" , "Septemtrigintillion" , "Octotrigintillion" , "Novemtrigintillion" ,
"Quardragintillion" , "Unquardragintillion" , "Duoquardragintillion" , "Trequardragintillion",
"Quattuorquardragintillion" , "Quinquardragintillion" , "Sexquardragintillion" , "Septenquardragintillion" ,
"Octoquardragintillion" , "Novemquardragintillion" , "Quinquagintillion" };

// Sets default values
ULargeFloat::ULargeFloat() : mValue(0), mExponent(0)
{
}

ULargeFloat* ULargeFloat::makeLargeFloat(float value, int exponent)
{
	ULargeFloat* res = NewObject<ULargeFloat>();
	res->mValue = value;
	res->mExponent = exponent;
	res->cleanValue();
	return res;
}

ULargeFloat* ULargeFloat::add(const ULargeFloat* rhs) const
{
	ULargeFloat* res = NewObject<ULargeFloat>();

	int expoDiff = rhs->mExponent - this->mExponent;

	if(std::abs(expoDiff) < csmPrecision)
	{ // within precision
		res->mValue = this->mValue + rhs->mValue * std::pow(10, expoDiff);
		res->mExponent = this->mExponent;

		res->cleanValue();
	}
	else if(expoDiff > 0) // use whichever is larger
	{
		res->mValue = rhs->mValue;
		res->mExponent = rhs->mExponent;
	}
	else
	{
		res->mValue = mValue;
		res->mExponent = mExponent;
	} 

	return res;
}

ULargeFloat* ULargeFloat::subtract(const ULargeFloat* rhs) const
{
	ULargeFloat* res = NewObject<ULargeFloat>();

	int expoDiff = rhs->mExponent - this->mExponent;

	if(std::abs(expoDiff) < csmPrecision)
	{ // within precision
		res->mValue = this->mValue - rhs->mValue * std::pow(10, expoDiff);
		res->mExponent = this->mExponent;

		res->cleanValue();
	}
	else if(expoDiff > 0) // use whichever is larger
	{
		res->mValue = -rhs->mValue;
		res->mExponent = rhs->mExponent;
	}
	else
	{
		res->mValue = mValue;
		res->mExponent = mExponent;
	}

	return res;
}

ULargeFloat* ULargeFloat::multiply(const ULargeFloat* rhs) const
{
	ULargeFloat* res = NewObject<ULargeFloat>();

	res->mValue = this->mValue * rhs->mValue;
	res->mExponent = this->mExponent + rhs->mExponent;
	res->cleanValue();

	return res;
}

ULargeFloat* ULargeFloat::divide(const ULargeFloat* rhs) const
{
	ULargeFloat* res = NewObject<ULargeFloat>();

	res->mValue = this->mValue / rhs->mValue;
	res->mExponent = this->mExponent - rhs->mExponent;
	res->cleanValue();

	return res;
}

bool ULargeFloat::greaterThan(const ULargeFloat* rhs) const
{
	if(mExponent > rhs->mExponent) // exponent is greater
		return true;
	else if(mExponent == rhs->mExponent) // expontent is equal
		return mValue > rhs->mValue; // is value greater
	else
		return false; // exponent is less
}

bool ULargeFloat::lessThan(const ULargeFloat* rhs) const
{
	if(mExponent < rhs->mExponent) // exponent is less
		return true;
	else if(mExponent == rhs->mExponent) // expontent is equal
		return mValue < rhs->mValue; // is value less
	else
		return false; // exponent is greater
}

bool ULargeFloat::equalTo(const ULargeFloat* rhs) const
{
	return mExponent == rhs->mExponent && mValue == rhs->mValue;
}

bool ULargeFloat::notEqualTo(const ULargeFloat* rhs) const
{
	return !equalTo(rhs);
}

bool ULargeFloat::greaterThanEqualTo(const ULargeFloat* rhs) const
{
	return equalTo(rhs) || greaterThan(rhs);
}

bool ULargeFloat::lessThanEqualTo(const ULargeFloat* rhs) const
{
	return equalTo(rhs) || lessThan(rhs);
}

FString ULargeFloat::toScientificNotation()
{
	return FString::Printf(TEXT("%.3f * 10 ^ %d"), this->mValue, this->mExponent);
}

FString ULargeFloat::toPostfixNotation()
{
	int idx = mExponent / 3;
	int mod = mExponent % 3;
	if(idx < csmLimit)
		return FString::Printf(TEXT("%.3f %s"), mValue * std::pow(10, mod), *csmPostfix[idx]);
	else
		return FString::Printf(TEXT("%.3f %s"), mValue * std::pow(10, mExponent - csmLimit * 3), *csmPostfix[csmLimit - 1]);
}

// Moves the decimal such that 0 <= value < 10.
// This will lose precision with exponents > 35.
void ULargeFloat::cleanValue()
{
	if(mValue == 0) // value is zero
	{
		mExponent = 0;
		return;
	}

	float v = std::abs(mValue); // should allow it to handle negative numbers
	while(v >= 10 || v < 1)
	{
		if(v >= 10)
		{
			mValue *= 0.1;
			mExponent++;
		}
		else
		{
			mValue *= 10;
			mExponent--;
		}
		v = std::abs(mValue);
	}
}
