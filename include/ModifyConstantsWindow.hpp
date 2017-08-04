/*
Copyright (c) 2017 InversePalindrome
InPal - ModifyConstantsWindow.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/minifram.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

#include <tuple>


class ModifyConstantsWindow : public wxMiniFrame
{
public:
	ModifyConstantsWindow(wxWindow* parent, MathDataDefault* mathData);

private:
	MathDataDefault* mathData;

	wxGridSizer* gridSizer;

	std::unordered_map <std::size_t, std::tuple<wxStaticText*, wxTextCtrl*, wxButton*>> constantWidgets;

	void OnModifyConstant(wxMouseEvent& event);
	void OnDeleteConstant(wxMouseEvent& event);
};