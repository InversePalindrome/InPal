/*
Copyright (c) 2017 InversePalindrome
InPal - ModifyVariablesWindow.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/minifram.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

#include <tuple>


class ModifyVariablesWindow : public wxMiniFrame
{
public:
	ModifyVariablesWindow(wxWindow* parent, MathDataDefault* mathData);

private:
	MathDataDefault* mathData;

	wxGridSizer* gridSizer;

	std::unordered_map<std::size_t, std::tuple<wxStaticText*, wxTextCtrl*, wxButton*>> variableWidgets;

	void OnModifyVariable(wxMouseEvent& event);
	void OnDeleteVariable(wxMouseEvent& event);
};