/*
Copyright (c) 2017 InversePalindrome
InPal - GraphSettingsWindow.cpp
InversePalindrome.com
*/


#include "GraphSettingsWindow.hpp"
#include "GrapherPanel.hpp"

#include <wx/sizer.h>
#include <wx/button.h>


GraphSettingsWindow::GraphSettingsWindow(wxWindow* parent, MathDataDefault* mathData) :
	wxMiniFrame(parent, wxID_ANY, "Graph Settings", wxDefaultPosition, wxDefaultSize, wxCAPTION | wxCLOSE_BOX),
	mathData(mathData),
	minXEntry(new wxTextCtrl(this, wxID_ANY, std::to_string(this->mathData->graphData.minX))),
	maxXEntry(new wxTextCtrl(this, wxID_ANY, std::to_string(this->mathData->graphData.maxX))),
	typeChoice()
{
	SetBackgroundColour(wxColor(128u, 128u, 128u));

	auto* topSizer = new wxBoxSizer(wxVERTICAL);
	auto* gridSizer = new wxGridSizer(2u, 3u, 0u, 0u);

	auto* minXText = new wxStaticText(this, wxID_ANY, "Min X");
	auto* maxXText = new wxStaticText(this, wxID_ANY, "Max X");

	auto& font = wxFont(8u, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

	auto* graphType = new wxStaticText(this, wxID_ANY, "Type");

	graphType->SetFont(font);
	minXText->SetFont(font);
	maxXText->SetFont(font);

	wxArrayString typeChoices;
	typeChoices.Add("Cartesian");
	typeChoices.Add("Polar");

	typeChoice = new wxChoice(this, wxID_APPLY, wxDefaultPosition, wxDefaultSize, typeChoices);
	typeChoice->SetStringSelection(mathData->graphData.graphType);

	gridSizer->Add(graphType, 0u, wxALL, 5u);
	gridSizer->Add(minXText, 0u, wxALL, 5u);
	gridSizer->Add(maxXText, 0u, wxALL, 5u);
	gridSizer->Add(typeChoice, 0u, wxALL, 5u);
	gridSizer->Add(minXEntry, 0u, wxALL, 5u);
	gridSizer->Add(maxXEntry, 0u, wxALL, 5u);
	
	auto* updateButton = new wxButton(this, wxID_ANY, "Update");

	topSizer->Add(gridSizer, 0u, wxALL, 5u);
	topSizer->Add(updateButton, 0u, wxALIGN_CENTER | wxALL, 5u);

	topSizer->Fit(this);
	topSizer->SetSizeHints(this);

	SetSizer(topSizer);

	updateButton->Bind(wxEVT_LEFT_DOWN, &GraphSettingsWindow::OnUpdate, this);
	typeChoice->Bind(wxEVT_CHOICE, &GrapherPanel::OnUpdateGraphType, dynamic_cast<GrapherPanel*>(wxFindWindowByName("GrapherPanel")));
}

void GraphSettingsWindow::OnUpdate(wxMouseEvent& event)
{
	try
	{
		this->mathData->graphData.minX = std::stod(this->minXEntry->GetValue().ToStdString());
		this->mathData->graphData.maxX = std::stod(this->maxXEntry->GetValue().ToStdString());
	}
	catch (const std::invalid_argument& e)
	{
		this->mathData->graphData.minX = -10;
		this->mathData->graphData.maxX = 10;
	}

	this->mathData->graphData.graphType = this->typeChoice->GetStringSelection();
	auto& minX = this->mathData->graphData.minX;
	auto& maxX = this->mathData->graphData.maxX;

	if (minX > maxX)
	{
		std::swap(minX, maxX);
	}

	this->mathData->graphData.plotWindow->Fit(minX, maxX, minX, maxX);

	this->Close();
}