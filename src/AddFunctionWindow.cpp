/*
Copyright (c) 2017 InversePalindrome
InPal - AddFunctionWindow.cpp
InversePalindrome.com
*/


#include "AddFunctionWindow.hpp"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>

#include <boost/algorithm/string.hpp>


AddFunctionWindow::AddFunctionWindow(wxWindow* parent, MathData<double>* mathData) :
	wxMiniFrame(parent, wxID_ANY, "Add Function", wxDefaultPosition, wxDefaultSize, wxCAPTION | wxCLOSE_BOX),
	mathData(mathData),
	nameEntry(new wxTextCtrl(this, wxID_ANY)),
	parameterEntry(new wxTextCtrl(this, wxID_ANY)),
	bodyEntry(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(250u, 300u), wxTE_MULTILINE))
{
	SetBackgroundColour(wxColor(128u, 128u, 128u));

	auto* sizer = new wxBoxSizer(wxVERTICAL);

	auto* nameText = new wxStaticText(this, wxID_ANY, "Name");
	auto* parameterText = new wxStaticText(this, wxID_ANY, "Parameters");
	auto* bodyText = new wxStaticText(this, wxID_ANY, "Body");

	auto& font = wxFont(8u, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

	nameText->SetFont(font);
	parameterText->SetFont(font);
	bodyText->SetFont(font);

	auto* addButton = new wxButton(this, wxID_ADD, "Add");

	sizer->Add(nameText, 0u, wxALL, 5u);
	sizer->Add(nameEntry, 0u, wxEXPAND | wxALL, 5u);
	sizer->Add(parameterText, 0u, wxALL, 5u);
	sizer->Add(parameterEntry, 0u, wxEXPAND | wxALL, 5u);
	sizer->Add(bodyText, 0u, wxALL, 5u);
	sizer->Add(bodyEntry, 0u, wxALL, 5u);
	sizer->Add(addButton, 0u, wxALIGN_CENTER | wxALL, 5u);

	sizer->Fit(this);
	sizer->SetSizeHints(this);

	SetSizer(sizer);

	addButton->Bind(wxEVT_LEFT_DOWN, &AddFunctionWindow::OnAddFunction, this);
}

void AddFunctionWindow::OnAddFunction(wxMouseEvent& event)
{
	if (nameEntry->IsEmpty())
	{
		return;
	}

	std::vector<std::string> parameterTokens;

	boost::split(parameterTokens, this->parameterEntry->GetValue().ToStdString(), boost::is_any_of(", "));
	
	this->mathData->mathSolver.addCompositorFunction(this->nameEntry->GetValue().ToStdString(), parameterTokens,
		this->bodyEntry->GetValue().ToStdString());

	this->mathData->functions.emplace(this->nameEntry->GetValue().ToStdString(), 
		std::make_pair(this->parameterEntry->GetValue().ToStdString(), this->bodyEntry->GetValue().ToStdString())); 

	this->nameEntry->Clear();
	this->parameterEntry->Clear();
	this->bodyEntry->Clear();
}