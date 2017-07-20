/*
Copyright (c) 2017 InversePalindrome
InPal - ModifyConstantsWindow.cpp
InversePalindrome.com
*/


#include "ModifyConstantsWindow.hpp"

#include <wx/button.h>
#include <wx/scrolwin.h>

#include <limits>


ModifyConstantsWindow::ModifyConstantsWindow(wxWindow* parent, MathData<double>* mathData) :
	wxMiniFrame(parent, wxID_ANY, "Modify Constants", wxDefaultPosition, wxDefaultSize, wxCAPTION | wxCLOSE_BOX),
	mathData(mathData),
	gridSizer(new wxGridSizer(mathData->constants.size(), 3u, 0u, 0u)),
	constantWidgets()
{
	SetBackgroundColour(wxColor(128u, 128u, 128u));

	auto* topSizer = new wxBoxSizer(wxVERTICAL);
	auto* labelSizer = new wxBoxSizer(wxHORIZONTAL);

	auto* nameText = new wxStaticText(this, wxID_ANY, "Name");
	auto* valueText = new wxStaticText(this, wxID_ANY, "Value");

	auto& font = wxFont(8u, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

	nameText->SetFont(font);
	valueText->SetFont(font);

	labelSizer->Add(nameText, 0u, wxRIGHT | wxLEFT, 50u);
	labelSizer->Add(valueText, 0u, wxRIGHT | wxLEFT, 50u);

	auto* scrollPanel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(400u, 250u));

	for (const auto& constant : mathData->constants)
	{
		auto* constantName = new wxStaticText(scrollPanel, wxID_ANY, constant.first);
		auto* valueText = new wxTextCtrl(scrollPanel, wxID_ANY, std::to_string(constant.second));
		auto* deleteButton = new wxButton(scrollPanel, NewControlId(), "Delete");

		gridSizer->Add(constantName, 0u, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 10u);
		gridSizer->Add(valueText, 0u, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 10u);
		gridSizer->Add(deleteButton, 0u, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 10u);

		constantWidgets.emplace(deleteButton->GetId(), std::make_tuple(constantName, valueText, deleteButton));

		deleteButton->Bind(wxEVT_LEFT_DOWN, &ModifyConstantsWindow::OnDeleteConstant, this);
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
	for (auto& widgetGroup : this->constantWidgets)
	{
		this->mathData->mathSolver.removeVariable(std::get<0>(widgetGroup.second)->GetLabel().ToStdString());

		double value;

		try
		{
			value = std::stod(std::get<1>(widgetGroup.second)->GetValue().ToStdString());
		}
		catch (const std::invalid_argument& e)
		{
			value = std::numeric_limits<double>::quiet_NaN();
		}

		this->mathData->constants.at(std::get<0>(widgetGroup.second)->GetLabel().ToStdString()) = value;

		this->mathData->mathSolver.addConstant(std::get<0>(widgetGroup.second)->GetLabel().ToStdString(), 
			this->mathData->constants.at(std::get<0>(widgetGroup.second)->GetLabel().ToStdString()));
	}

	this->Close(true);
}

void ModifyConstantsWindow::OnDeleteConstant(wxMouseEvent& event)
{
	auto& widgetGroup = this->constantWidgets.at(event.GetId());

	this->mathData->mathSolver.removeVariable(std::get<0>(widgetGroup)->GetLabel().ToStdString());

	this->mathData->constants.at(std::get<0>(widgetGroup)->GetLabel().ToStdString()) = std::numeric_limits<double>::quiet_NaN();

	this->mathData->mathSolver.addConstant(std::get<0>(widgetGroup)->GetLabel().ToStdString(),
		this->mathData->constants.at(std::get<0>(widgetGroup)->GetLabel().ToStdString()));

	this->mathData->constants.erase(std::get<0>(widgetGroup)->GetLabel().ToStdString());

	std::get<0>(widgetGroup)->Destroy();
	std::get<1>(widgetGroup)->Destroy();
	std::get<2>(widgetGroup)->Destroy();

	this->gridSizer->Layout();
}