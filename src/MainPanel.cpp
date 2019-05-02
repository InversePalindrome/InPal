/*
Copyright (c) 2017 InversePalindrome
InPal - MainPanel.cpp
InversePalindrome.com
*/


#include "MainPanel.hpp"

#include <wx/sizer.h>

#include <boost/format.hpp>


MainPanel::MainPanel(wxWindow* parent, MathData<double>* mathData) :
    wxPanel(parent, wxID_ANY),
    mathData(mathData),
    taskEntry(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(700u, 600u), wxTE_MULTILINE)),
    taskSolution(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(700u, 50u), wxTE_READONLY)),
    solveButton(new wxButton(this, wxID_ANY, "Solve")),
    clearButton(new wxButton(this, wxID_ANY, "Clear"))
{
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

    solveButton->Bind(wxEVT_LEFT_DOWN, &MainPanel::OnSolveTask, this);
    clearButton->Bind(wxEVT_LEFT_DOWN, &MainPanel::OnClearTask, this);
}

void MainPanel::OnSolveTask(wxMouseEvent & event)
{
    this->mathData->mathSolver.setTask(taskEntry->GetValue().ToStdString());
    this->mathData->mathSolver.solve();

    this->taskSolution->SetValue(boost::str(boost::format("%.15f") % this->mathData->mathSolver.getValue()));
}

void MainPanel::OnClearTask(wxMouseEvent & event)
{
    this->mathData->mathSolver.clearTask();

    this->taskEntry->Clear();
    this->taskSolution->Clear();
}


