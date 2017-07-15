/*
Copyright (c) 2017 InversePalindrome
InPal - ModifyVariablesWindow.cpp
InversePalindrome.com
*/


#include "ModifyVariablesWindow.hpp"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/scrolwin.h>


ModifyVariablesWindow::ModifyVariablesWindow(wxWindow* parent, MathData<double>* mathData) :
	wxMiniFrame(parent, wxID_ANY, "Modify Variables", wxDefaultPosition, wxDefaultSize, wxCAPTION | wxCLOSE_BOX),
	mathData(mathData),
	variableEntries()
{
	SetBackgroundColour(wxColor(192u, 197u, 206u));
	
	auto* topSizer = new wxBoxSizer(wxVERTICAL);
	auto* labelSizer = new wxBoxSizer(wxHORIZONTAL);

	auto* nameText = new wxStaticText(this, wxID_ANY, "Name");
	auto* valueText = new wxStaticText(this, wxID_ANY, "Value");

	auto& font = nameText->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	
	nameText->SetFont(font);
	valueText->SetFont(font);

	labelSizer->Add(nameText, 0u, wxRIGHT | wxLEFT, 50u);
	labelSizer->Add(valueText, 0u, wxRIGHT | wxLEFT, 50u);

	auto* scrollPanel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(260u, 200u));
	auto* gridSizer = new wxGridSizer(mathData->variables.size(), 2u, 0u, 0u);

	for (const auto& variable : mathData->variables)
	{
		auto* variableName = new wxStaticText(scrollPanel, wxID_ANY, variable.first);
		auto* valueText = new wxTextCtrl(scrollPanel, wxID_ANY, std::to_string(variable.second));

		gridSizer->Add(variableName, 0u, wxALL | wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL, 10u);
		gridSizer->Add(valueText, 0u, wxALL | wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL, 10u);

		variableEntries.emplace(variable.first, valueText);
	}

	scrollPanel->SetSizer(gridSizer);

	scrollPanel->FitInside();
	scrollPanel->SetScrollRate(0u, 10u);

	auto* modifyButton = new wxButton(this, wxID_ANY, "Modify");

	topSizer->AddSpacer(5u);
	topSizer->Add(labelSizer, 0u);
	topSizer->Add(scrollPanel, 0u, wxEXPAND | wxALL);
	topSizer->Add(modifyButton, 0u, wxALIGN_CENTER | wxALL, 5u);

	topSizer->Fit(this);
	topSizer->SetSizeHints(this);

	SetSizer(topSizer);

	modifyButton->Bind(wxEVT_LEFT_DOWN, &ModifyVariablesWindow::OnModifyVariable, this);
}

void ModifyVariablesWindow::OnModifyVariable(wxMouseEvent& event)
{
	for (const auto& variableEntry : this->variableEntries)
	{
		this->mathData->variables.at(variableEntry.first) = std::stod(variableEntry.second->GetValue().ToStdString());
	}

	this->Close(true);
}