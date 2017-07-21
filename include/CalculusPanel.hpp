/*
Copyright (c) 2017 InversePalindrome
InPal - CalculusPanel.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/textctrl.h>


class CalculusPanel : public wxPanel
{
public:
	CalculusPanel(wxWindow* parent, MathData<double>* mathData);

private:
	MathData<double>* mathData;

	wxChoice* derivativeChoice;

	wxTextCtrl* derivativeEntry;
	wxTextCtrl* xPositionEntry;
	wxTextCtrl* derivativeSolution;

	wxTextCtrl* integralEntry;
	wxTextCtrl* initialXEntry;
	wxTextCtrl* finalXEntry;
	wxTextCtrl* integralSolution;

	void OnSolveDerivative(wxMouseEvent& event);
	void OnSolveIntegral(wxMouseEvent& event);

	void OnClearDerivative(wxMouseEvent& event);
	void OnClearIntegral(wxMouseEvent& event);
};
