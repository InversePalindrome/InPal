/*
Copyright (c) 2017 InversePalindrome
InPal - TabBar.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/notebook.h>


class TabBar : public wxNotebook
{
public:
	TabBar(wxWindow* parent, MathData<double>* mathData);
};