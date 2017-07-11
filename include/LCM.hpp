/*
Copyright (c) 2017 InversePalindrome
InPal - LCM.hpp
InversePalindrome.com
*/


#pragma once

#include "Exprtk.hpp"
#include "GCD.hpp"


template<typename T>
struct LCM : public exprtk::ivararg_function<T>
{
	inline T operator()(const std::vector<T>& argList)
	{
		T result = argList.at(0u);

		for (std::size_t i = 1u; i < argList.size(); ++i)
		{
			result = this->lcm(result, argList.at(i));
		}

		return result;
	}

	inline static T lcm(T a, T b)
	{
		return (a * b) / GCD<T>::gcd(a, b);
	}
};