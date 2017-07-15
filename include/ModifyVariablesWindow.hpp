/*
Copyright (c) 2017 InversePalindrome
InPal - ModifyVariablesWindow.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/minifram.h>
#include <wx/textctrl.h>


class ModifyVariablesWindow : public wxMiniFrame
{
public:
	ModifyVariablesWindow(wxWindow* parent, MathData<double>* mathData);

private:
	MathData<double>* mathData;

	std::unordered_map<std::string, wxTextCtrl*> variableEntries;

	void OnModifyVariable(wxMouseEvent& event);
};