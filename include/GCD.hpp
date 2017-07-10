/*
Copyright (c) 2017 InversePalindrome
InPal - GCD.hpp
InversePalindrome.com
*/


#pragma once

#include "Exprtk.hpp"

#include <numeric>


template<typename T>
struct GCD : public exprtk::ivararg_function<T>
{
	inline T operator()(const std::vector<T>& argList)
	{
		T result = argList.at(0u);

		for (std::size_t i = 1; i < argList.size(); ++i)
		{
			result = this->gcd(result, argList.at(i));
		}

		return result;
	}

	inline static T gcd(T a, T b)
	{
		return b == 0 ? a : gcd(b, std::fmod(a, b));
	}
};