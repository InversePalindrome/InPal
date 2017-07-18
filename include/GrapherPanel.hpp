/*
Copyright (c) 2017 InversePalindrome
InPal - GrapherPanel.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/mathplot.h>


class GrapherPanel : public wxPanel
{
public:
	GrapherPanel(wxWindow* parent, MathData<double>* mathData);

private:
	MathData<double>* mathData;

	mpWindow* plotWindow;
	mpFXYVector* functionLayer;

	wxTextCtrl* graphEntry;

	void OnGraphButton(wxMouseEvent& event);
};