/*
Copyright (c) 2017 InversePalindrome
InPal - ModifyConstantsWindow.cpp
InversePalindrome.com
*/


#include "ModifyConstantsWindow.hpp"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/scrolwin.h>


ModifyConstantsWindow::ModifyConstantsWindow(wxWindow* parent, MathData<double>* mathData) :
	wxMiniFrame(parent, wxID_ANY, "Modify Constants", wxDefaultPosition, wxDefaultSize, wxCAPTION | wxCLOSE_BOX),
	mathData(mathData),
	constantEntries()
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
	auto* gridSizer = new wxGridSizer(mathData->constants.size(), 2u, 0u, 0u);

	for (const auto& constant : mathData->constants)
	{
	    auto* constantName = new wxStaticText(scrollPanel, wxID_ANY, constant.first);
	    auto* valueText = new wxTextCtrl(scrollPanel, wxID_ANY, std::to_string(constant.second));

	    gridSizer->Add(constantName, 0u, wxALL | wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL, 10u);
	    gridSizer->Add(valueText, 0u, wxALL | wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL, 10u);

		constantEntries.emplace(constant.first, valueText);
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

	modifyButton->Bind(wxEVT_LEFT_DOWN, &ModifyConstantsWindow::OnModifyConstant, this);
}

void ModifyConstantsWindow::OnModifyConstant(wxMouseEvent& event)
{
	for (const auto& constantEntry : this->constantEntries)
	{
		this->mathData->mathSolver.removeConstant(constantEntry.first);

		this->mathData->constants.at(constantEntry.first) = std::stod(constantEntry.second->GetValue().ToStdString());

		this->mathData->mathSolver.addConstant(constantEntry.first, this->mathData->constants.at(constantEntry.first));
	}

	this->Close(true);
}