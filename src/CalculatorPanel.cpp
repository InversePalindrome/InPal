/*
Copyright (c) 2017 InversePalindrome
InPal - MainPanel.cpp
InversePalindrome.com
*/


#include "CalculatorPanel.hpp"

#include <wx/sizer.h>

#include <boost/format.hpp>
#include <boost/algorithm/string/trim.hpp>


CalculatorPanel::CalculatorPanel(wxWindow* parent, MathDataDefault* mathData) :
    wxPanel(parent, wxID_ANY),
    mathData(mathData),
    taskEntry(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(700u, 600u), wxTE_MULTILINE)),
    taskSolution(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(700u, 50u), wxTE_READONLY)),
    solveButton(new wxButton(this, wxID_ANY, "Solve")),
    clearButton(new wxButton(this, wxID_ANY, "Clear"))
{
    SetBackgroundColour(wxColor(128u, 128u, 128u));

    auto* topSizer = new wxBoxSizer(wxVERTICAL);
    auto* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    topSizer->Add(taskSolution, 0u, wxEXPAND | wxALL, 10u);
    topSizer->AddSpacer(20u);

    buttonSizer->Add(solveButton, 0u, wxALIGN_CENTER);
    buttonSizer->AddSpacer(5u);
    buttonSizer->Add(clearButton, 0u, wxALIGN_CENTER);

    topSizer->Add(buttonSizer, 0u, wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL);

    topSizer->AddSpacer(10u);

    topSizer->Add(taskEntry, 0u, wxEXPAND | wxALL, 10u);

    topSizer->Fit(this);
    topSizer->SetSizeHints(this);

    SetSizer(topSizer);

    taskSolution->SetFont(wxFont(30u, wxFontFamily::wxFONTFAMILY_DEFAULT, wxFontStyle::wxFONTSTYLE_NORMAL, wxFontWeight::wxFONTWEIGHT_BOLD));
    taskEntry->SetFont(wxFont(18u, wxFontFamily::wxFONTFAMILY_DEFAULT, wxFontStyle::wxFONTSTYLE_NORMAL, wxFontWeight::wxFONTWEIGHT_BOLD));

    solveButton->Bind(wxEVT_LEFT_DOWN, &CalculatorPanel::OnSolveTask, this);
    clearButton->Bind(wxEVT_LEFT_DOWN, &CalculatorPanel::OnClearTask, this);
}

void CalculatorPanel::OnSolveTask(wxMouseEvent & event)
{
    this->mathData->mathSolver.setTask(this->taskEntry->GetValue().ToStdString());

    if (this->mathData->mathSolver.solve())
    {
        auto& result = boost::str(boost::format("%.18f") % this->mathData->mathSolver.getValue());
        boost::trim_right_if(result, boost::is_any_of("0"));
        boost::trim_right_if(result, boost::is_any_of("."));

        this->taskSolution->SetValue(result);
    }
    else
    {
        this->taskSolution->SetValue("nan");
    }
}

void CalculatorPanel::OnClearTask(wxMouseEvent & event)
{
    this->mathData->mathSolver.clearTask();

    this->taskEntry->Clear();
    this->taskSolution->Clear();
}


