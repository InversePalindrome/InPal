/*
Copyright (c) 2017 InversePalindrome
InPal - AddFunctionWindow.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/minifram.h>
#include <wx/textctrl.h>


class AddFunctionWindow : public wxMiniFrame
{
public:
	AddFunctionWindow(wxWindow* parent, MathDataDefault* mathData);

private:
	MathDataDefault* mathData;

	wxTextCtrl* nameEntry;
	wxTextCtrl* parameterEntry;
	wxTextCtrl* bodyEntry;

	void OnAddFunction(wxMouseEvent& event);
};