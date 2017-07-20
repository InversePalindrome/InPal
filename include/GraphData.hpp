/*
Copyright (c) 2017 InversePalindrome
InPal - GraphData.cpp
InversePalindrome.com
*/


#pragma once

#include <wx/mathplot.h>


struct GraphData
{
	mpWindow* plotWindow;
	std::vector<mpFXYVector*> graphs;

	double minX;
	double maxX;
};