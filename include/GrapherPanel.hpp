/*
Copyright (c) 2017 InversePalindrome
InPal - GrapherPanel.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/mathplot.h>


class GrapherPanel : public wxPanel
{
public:
	GrapherPanel(wxWindow* parent, MathDataDefault* mathData);

	void OnUpdateGraphType(wxCommandEvent& event);

private:
	MathDataDefault* mathData;

	wxStaticText* graphText;
	wxTextCtrl* graphEntry;

	void graphCartesian(std::vector<double>& xCoordinates, std::vector<double>& yCoordinates,
		std::size_t numberOfPoints, double minX, double maxX);
	void graphPolar(std::vector<double>& xCoordinates, std::vector<double>& yCoordinates, std::size_t numberOfPoints);

	void OnGraphButton(wxMouseEvent& event);
};