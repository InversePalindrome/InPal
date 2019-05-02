/*
Copyright (c) 2017 InversePalindrome
InPal - ModifyVariablesWindow.cpp
InversePalindrome.com
*/


#include "ModifyVariablesWindow.hpp"

#include <wx/button.h>
#include <wx/scrolwin.h>


ModifyVariablesWindow::ModifyVariablesWindow(wxWindow* parent, MathDataDefault* mathData) :
    wxMiniFrame(parent, wxID_ANY, "Modify Variables", wxDefaultPosition, wxDefaultSize, wxCAPTION | wxCLOSE_BOX),
    mathData(mathData),
    gridSizer(new wxGridSizer(mathData->variables.size(), 3u, 0u, 0u)),
    variableWidgets()
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

    for (const auto& variable : mathData->variables)
    {
        auto* variableName = new wxStaticText(scrollPanel, wxID_ANY, variable.first);
        auto* valueText = new wxTextCtrl(scrollPanel, wxID_ANY, std::to_string(variable.second));
        auto* deleteButton = new wxButton(scrollPanel, NewControlId(), "Delete");

        gridSizer->Add(variableName, 0u, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 10u);
        gridSizer->Add(valueText, 0u, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 10u);
        gridSizer->Add(deleteButton, 0u, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 10u);

        variableWidgets.emplace(deleteButton->GetId(), std::make_tuple(variableName, valueText, deleteButton));

        deleteButton->Bind(wxEVT_LEFT_DOWN, &ModifyVariablesWindow::OnDeleteVariable, this);
    }

    scrollPanel->SetSizer(gridSizer);

    scrollPanel->FitInside();
    scrollPanel->SetScrollRate(10u, 10u);

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

void ModifyVariablesWindow::OnModifyVariable(wxMouseEvent & event)
{
    for (auto& widgetGroup : this->variableWidgets)
    {
        long double value;

        try
        {
            value = std::stold(std::get<1>(widgetGroup.second)->GetValue().ToStdString());
        }
        catch (const std::invalid_argument & e)
        {
            value = std::numeric_limits<long double>::quiet_NaN();
        }

        this->mathData->variables.at(std::get<0>(widgetGroup.second)->GetLabel().ToStdString()) = value;
    }

    this->Close(true);
}

void ModifyVariablesWindow::OnDeleteVariable(wxMouseEvent & event)
{
    auto& widgetGroup = this->variableWidgets.at(event.GetId());

    this->mathData->variables.erase(std::get<0>(widgetGroup)->GetLabel().ToStdString());
    this->mathData->mathSolver.removeVariable(std::get<0>(widgetGroup)->GetLabel().ToStdString());

    std::get<0>(widgetGroup)->Destroy();
    std::get<1>(widgetGroup)->Destroy();
    std::get<2>(widgetGroup)->Destroy();

    this->gridSizer->Layout();
}