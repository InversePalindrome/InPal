/*
Copyright (c) 2017 InversePalindrome
InPal - GrapherPanel.cpp
InversePalindrome.com
*/


#include "GrapherPanel.hpp"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>


GrapherPanel::GrapherPanel(wxWindow* parent, MathData<double>* mathData) :
	wxPanel(parent, wxID_ANY),
	mathData(mathData),
	plotWindow(new mpWindow(this, wxID_ANY, wxDefaultPosition, wxSize(100u, 100u), wxSUNKEN_BORDER)),
	functionLayer(new mpFXYVector("Hi")),
	graphEntry(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(550u, 0u)))
{
	SetBackgroundColour(wxColor(128u, 128u, 128u));
	
	auto* topSizer = new wxBoxSizer(wxVERTICAL);
	auto* bottomSizer = new wxBoxSizer(wxHORIZONTAL);

	auto* xAxis = new mpScaleX("X", mpALIGN_BOTTOM);
	auto* yAxis = new mpScaleY("Y", mpALIGN_LEFT);

	plotWindow->AddLayer(xAxis);
	plotWindow->AddLayer(yAxis);
	plotWindow->SetMPScrollbars(false);
	plotWindow->EnableDoubleBuffer(true);
	plotWindow->Fit();
	
	auto* graphText = new wxStaticText(this, wxID_ANY, "y = ");
	auto* graphButton = new wxButton(this, wxID_ANY, "Graph");

	auto& font = graphText->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	font.SetPointSize(16);

	graphText->SetFont(font);
	graphEntry->SetFont(font);

	bottomSizer->Add(graphText, 0u, wxALL, 2u);
	bottomSizer->Add(graphEntry, 0u, wxALL | wxEXPAND, 2u);
	bottomSizer->Add(graphButton, 0u, wxALL, 5u);

	topSizer->Add(plotWindow, 1u, wxALL | wxEXPAND, 10u);
	topSizer->Add(bottomSizer, 0u, wxALL, 10u);

	topSizer->Fit(this);
	topSizer->SetSizeHints(this);

	SetSizer(topSizer);

	graphButton->Bind(wxEVT_LEFT_DOWN, &GrapherPanel::OnGraphButton, this);
}

void GrapherPanel::OnGraphButton(wxMouseEvent& event)
{

}