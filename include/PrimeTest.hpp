/*
Copyright (c) 2017 InversePalindrome
InPal - PrimeTest.hpp
InversePalindrome.com
*/


#pragma once

#include "Exprtk.hpp"


template<typename T>
struct PrimeTest : public exprtk::ifunction<T>
{
	PrimeTest() :
		exprtk::ifunction<T>(1u)
	{
	}

	inline T operator()(const T& number)
	{
		return isPrime(static_cast<std::size_t>(number));
	}

	inline static bool isPrime(std::size_t number)
	{
		if (number < 2u)
		{
			return false;
		}
		else if (number == 2u)
		{
			return true;
		}
		else if (number % 2 == 0u)
		{
			return false;
		}

		for (std::size_t i = 3u; i * i <= number; i += 2)
		{
			if (number % i == 0u)
			{
				return false;
			}
		}

		return true;
	}
};