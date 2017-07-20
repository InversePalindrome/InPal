/*
Copyright (c) 2017 InversePalindrome
InPal - AddVariableWindow.cpp
InversePalindrome.com
*/


#include "AddVariableWindow.hpp"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>


AddVariableWindow::AddVariableWindow(wxWindow* parent, MathData<double>* mathData) :
	wxMiniFrame(parent, wxID_ANY, "Add Variable", wxDefaultPosition, wxSize(250u, 200u), wxCAPTION | wxCLOSE_BOX),
	mathData(mathData),
	nameEntry(new wxTextCtrl(this, wxID_ANY)),
	valueEntry(new wxTextCtrl(this, wxID_ANY))
{
	SetBackgroundColour(wxColor(128u, 128u, 128u));

	auto* topSizer = new wxBoxSizer(wxVERTICAL);
	auto* gridSizer = new wxGridSizer(2u, 2u, 0u, 0u);

	auto* nameText = new wxStaticText(this, wxID_ANY, "Name");
	auto* valueText = new wxStaticText(this, wxID_ANY, "Value");

	auto& font = wxFont(8u, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

	nameText->SetFont(font);
	valueText->SetFont(font);

	auto* addButton = new wxButton(this, wxID_ADD, "Add");

	gridSizer->Add(nameText, 0u, wxALL, 5u);
	gridSizer->Add(valueText, 0u, wxALL, 5u);

	gridSizer->Add(nameEntry, 0u, wxALL, 5u);
	gridSizer->Add(valueEntry, 0u, wxALL, 5u);

	topSizer->Add(gridSizer);
	topSizer->Add(addButton, 0u, wxALIGN_CENTER | wxALL, 5u);

	topSizer->Fit(this);
	topSizer->SetSizeHints(this);

	SetSizer(topSizer);

	addButton->Bind(wxEVT_LEFT_DOWN, &AddVariableWindow::OnAddVariable, this);
}

void AddVariableWindow::OnAddVariable(wxMouseEvent& event)
{
	const auto& variableName = this->nameEntry->GetValue().ToStdString();

	double value;

	try
	{
		value = std::stod(this->valueEntry->GetValue().ToStdString());
	}
	catch (const std::invalid_argument& e)
	{
		value = std::numeric_limits<double>::quiet_NaN();
	}

	if (!variableName.empty())
	{
		this->mathData->variables.emplace(variableName, value);

		this->mathData->mathSolver.addVariable(variableName, this->mathData->variables.at(variableName));
	}

	this->nameEntry->Clear();
	this->valueEntry->Clear();

	this->Layout();
}