/*
Copyright (c) 2017 InversePalindrome
InPal - GrapherPanel.cpp
InversePalindrome.com
*/


#include "GrapherPanel.hpp"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/choice.h>

#include <boost/algorithm/string/replace.hpp>
#include <boost/math/constants/constants.hpp>

#include <algorithm>


GrapherPanel::GrapherPanel(wxWindow* parent, MathData<double>* mathData) :
	wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "GrapherPanel"),
	mathData(mathData),
	graphText(new wxStaticText(this, wxID_ANY, "F(x) = ")),
	graphEntry(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(550u, 0u)))
{
	SetBackgroundColour(wxColor(128u, 128u, 128u));

	mathData->graphData.plotWindow = new mpWindow(this, wxID_ANY, wxDefaultPosition, wxSize(100u, 100u), wxSUNKEN_BORDER);
	mathData->graphData.graphType = "Cartesian";
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

void GrapherPanel::OnUpdateGraphType(wxCommandEvent& event)
{
	const auto& typeSelection = dynamic_cast<wxChoice*>(this->FindWindowById(wxID_APPLY))->GetStringSelection();

	if (typeSelection == "Cartesian")
	{
		this->graphText->SetLabel("F(x) = ");
	}
	else if (typeSelection == "Polar")
	{
		this->graphText->SetLabel("r(t) = ");
	}
}

void GrapherPanel::graphCartesian(std::vector<double>& xCoordinates, std::vector<double>& yCoordinates,
	std::size_t numberOfPoints, double minX, double maxX)
{
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
}

void GrapherPanel::graphPolar(std::vector<double>& xCoordinates, std::vector<double>& yCoordinates, std::size_t numberOfPoints)
{
	const auto& pi = boost::math::constants::pi<double>();

	for (double i = 0.0; i <= 2.0 * pi; i += (2 * pi) / numberOfPoints)
	{
		auto graphEquation = this->graphEntry->GetValue().ToStdString();

		boost::replace_all(graphEquation, "t", "(" + std::to_string(i) + ")");

		this->mathData->mathSolver.setTask(graphEquation);

		if (mathData->mathSolver.solve())
		{
			xCoordinates.push_back(this->mathData->mathSolver.getValue() * std::cos(i));
			yCoordinates.push_back(this->mathData->mathSolver.getValue() * std::sin(i));
		}
	}
}

void GrapherPanel::OnGraphButton(wxMouseEvent& event)
{
	const std::size_t numberOfPoints = 2500u;

	std::vector<double> xCoordinates;
	std::vector<double> yCoordinates;

	double minX = this->mathData->graphData.minX;
	double maxX = this->mathData->graphData.maxX;

	if (mathData->graphData.graphType == "Cartesian")
	{
		this->graphCartesian(xCoordinates, yCoordinates, numberOfPoints, minX, maxX);
	}
	else if (mathData->graphData.graphType == "Polar")
	{
		this->graphPolar(xCoordinates, yCoordinates, numberOfPoints);
	}

	this->mathData->graphData.graphs.push_back(new mpFXYVector(this->graphEntry->GetValue().ToStdString()));
	this->mathData->graphData.graphs.back()->SetData(xCoordinates, yCoordinates);
	this->mathData->graphData.graphs.back()->SetContinuity(true);
	this->mathData->graphData.graphs.back()->ShowName(false);
	
	this->mathData->graphData.plotWindow->AddLayer(this->mathData->graphData.graphs.back());

	this->mathData->graphData.plotWindow->Fit();
}