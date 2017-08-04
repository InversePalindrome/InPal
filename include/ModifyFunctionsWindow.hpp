/*
Copyright (c) 2017 InversePalindrome
InPal - ModifyFunctionsWindow.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/minifram.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>


class ModifyFunctionsWindow : public wxMiniFrame
{
public:
	ModifyFunctionsWindow(wxWindow* parent, MathDataDefault* mathData);

private:
	MathDataDefault* mathData;

	wxPanel* mainPanel;
	wxPanel* secondaryPanel;
	wxBoxSizer* mainSizer;

	wxStaticText* functionName;
	wxTextCtrl* parametersEntry;
	wxTextCtrl* bodyEntry;

	void OnSelectFunction(wxMouseEvent& event);
	void OnModifyFunction(wxMouseEvent& event);
	void OnDeleteFunction(wxMouseEvent& event);
};