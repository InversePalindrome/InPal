/*
Copyright (c) 2017 InversePalindrome
InPal - AddVariableWindow.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/minifram.h>
#include <wx/textctrl.h>


class AddVariableWindow : public wxMiniFrame
{
public:
	AddVariableWindow(wxWindow* parent, MathDataDefault* mathData);

private:
	MathDataDefault* mathData;

	wxTextCtrl* nameEntry;
	wxTextCtrl* valueEntry;

	void OnAddVariable(wxMouseEvent& event);
};