/*
Copyright (c) 2017 InversePalindrome
InPal - GraphData.hpp
InversePalindrome.com
*/


#pragma once

#include <wx/mathplot.h>

#include <string>


struct GraphData
{
    mpWindow* plotWindow;
    std::string graphType;
    std::vector<mpFXYVector*> graphs;

    double minX;
    double maxX;
};