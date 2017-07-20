/*
Copyright (c) 2017 InversePalindrome
InPal - MathData.hpp
InversePalindrome.com
*/


#pragma once

#include "MathSolver.hpp"
#include "GraphData.hpp"

#include <unordered_map>


template<typename T>
struct MathData
{
	MathSolver<T> mathSolver;
	GraphData graphData;

	std::unordered_map<std::string, T> variables;
	std::unordered_map<std::string, T> constants;
	std::unordered_map<std::string, std::pair<std::string, std::string>> functions;
};