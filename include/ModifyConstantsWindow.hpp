/*
Copyright (c) 2017 InversePalindrome
InPal - ModifyConstantsWindow.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/minifram.h>
#include <wx/textctrl.h>

#include <unordered_map>


class ModifyConstantsWindow : public wxMiniFrame
{
public:
	ModifyConstantsWindow(wxWindow* parent, MathData<double>* mathData);

private:
	MathData<double>* mathData;

	std::unordered_map<std::string, wxTextCtrl*> constantEntries;

	void OnModifyConstant(wxMouseEvent& event);
};