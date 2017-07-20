/*
Copyright (c) 2017 InversePalindrome
InPal - GrapherPanel.cpp
InversePalindrome.com
*/


#include "GrapherPanel.hpp"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>

#include <boost/algorithm/string/replace.hpp>

#include <algorithm>


GrapherPanel::GrapherPanel(wxWindow* parent, MathData<double>* mathData) :
	wxPanel(parent, wxID_ANY),
	mathData(mathData),
	graphEntry(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(550u, 0u)))
{
	SetBackgroundColour(wxColor(128u, 128u, 128u));

	mathData->graphData.plotWindow = new mpWindow(this, wxID_ANY, wxDefaultPosition, wxSize(100u, 100u), wxSUNKEN_BORDER);
	mathData->graphData.minX = -10;
	mathData->graphData.maxX = 10;

	auto* topSizer = new wxBoxSizer(wxVERTICAL);
	auto* bottomSizer = new wxBoxSizer(wxHORIZONTAL);

	mathData->graphData.plotWindow->AddLayer(new mpScaleX("X", mpALIGN_CENTER));
	mathData->graphData.plotWindow->AddLayer(new mpScaleY("Y", mpALIGN_CENTER));
	mathData->graphData.plotWindow->SetMPScrollbars(false);
	mathData->graphData.plotWindow->EnableMousePanZoom(false);
	mathData->graphData.plotWindow->Fit(mathData->graphData.minX, mathData->graphData.maxX,
		mathData->graphData.minX, mathData->graphData.maxX);

	auto* graphText = new wxStaticText(this, wxID_ANY, "y = ");
	auto* graphButton = new wxButton(this, wxID_ANY, "Graph");

	auto& font = wxFont(16u, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

	graphText->SetFont(font);
	graphEntry->SetFont(font);

	bottomSizer->Add(graphText, 0u, wxALL, 2u);
	bottomSizer->Add(graphEntry, 0u, wxALL | wxEXPAND, 2u);
	bottomSizer->Add(graphButton, 0u, wxALL, 5u);

	topSizer->Add(mathData->graphData.plotWindow, 1u, wxALL | wxEXPAND, 10u);
	topSizer->Add(bottomSizer, 0u, wxALL, 10u);

	topSizer->Fit(this);
	topSizer->SetSizeHints(this);

	SetSizer(topSizer);

	graphButton->Bind(wxEVT_LEFT_DOWN, &GrapherPanel::OnGraphButton, this);
}

void GrapherPanel::OnGraphButton(wxMouseEvent& event)
{
	const std::size_t numberOfPoints = 2500u;

	std::vector<double> xCoordinates;
	std::vector<double> yCoordinates;

	double minX = this->mathData->graphData.minX;
	double maxX = this->mathData->graphData.maxX;

	for (double i = minX; i <= maxX; i += std::abs(maxX - minX) / numberOfPoints)
	{
		auto graphEquation = this->graphEntry->GetValue().ToStdString();

		boost::replace_all(graphEquation, "x", "(" + std::to_string(i) + ")");

		this->mathData->mathSolver.setTask(graphEquation);

		if (this->mathData->mathSolver.solve())
		{
			xCoordinates.push_back(i);
			yCoordinates.push_back(this->mathData->mathSolver.getValue());
		}
	}

	this->mathData->graphData.graphs.push_back(new mpFXYVector(this->graphEntry->GetValue().ToStdString()));
	this->mathData->graphData.graphs.back()->SetData(xCoordinates, yCoordinates);
	this->mathData->graphData.graphs.back()->SetContinuity(true);
	this->mathData->graphData.graphs.back()->ShowName(false);
	
	this->mathData->graphData.plotWindow->AddLayer(this->mathData->graphData.graphs.back());

	this->mathData->graphData.plotWindow->Fit();
}