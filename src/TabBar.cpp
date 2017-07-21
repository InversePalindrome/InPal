/*
Copyright (c) 2017 InversePalindrome
InPal - TabBar.cpp
InversePalindrome.com
*/


#include "TabBar.hpp"
#include "GrapherPanel.hpp"
#include "CalculusPanel.hpp"
#include "CalculatorPanel.hpp"


TabBar::TabBar(wxWindow* parent, MathData<double>* mathData) :
	wxNotebook(parent, wxID_ANY)
{
	AddPage(new CalculatorPanel(this, mathData), "Calculator");
	AddPage(new GrapherPanel(this, mathData), "Grapher");
	AddPage(new CalculusPanel(this, mathData), "Calculus");
}