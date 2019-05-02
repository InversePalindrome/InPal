/*
Copyright (c) 2017 InversePalindrome
InPal - GraphFunctionsWindow.cpp
InversePalindrome.com
*/


#include "GraphFunctionsWindow.hpp"

#include <wx/sizer.h>
#include <wx/scrolwin.h>

#include <algorithm>


GraphFunctionsWindow::GraphFunctionsWindow(wxWindow* parent, MathDataDefault* mathData) :
    wxMiniFrame(parent, wxID_ANY, "Graph Functions", wxDefaultPosition, wxDefaultSize, wxCAPTION | wxCLOSE_BOX),
    mathData(mathData),
    functionWidgets()
{
    SetBackgroundColour(wxColor(128u, 128u, 128u));

    auto* topSizer = new wxBoxSizer(wxVERTICAL);
    auto* labelSizer = new wxBoxSizer(wxHORIZONTAL);
    auto* gridSizer = new wxGridSizer(mathData->graphData.graphs.size(), 3u, 0u, 0u);

    auto* functionText = new wxStaticText(this, wxID_ANY, "Function");
    auto* colorText = new wxStaticText(this, wxID_ANY, "Color");

    auto& font = wxFont(8u, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    functionText->SetFont(font);
    colorText->SetFont(font);

    labelSizer->Add(functionText, 0u, wxRIGHT | wxLEFT, 50u);
    labelSizer->Add(colorText, 0u, wxRIGHT | wxLEFT, 50u);

    auto* scrollPanel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(400u, 250));

    wxArrayString colorChoices;
    colorChoices.Add("Black");
    colorChoices.Add("Blue");
    colorChoices.Add("Red");
    colorChoices.Add("Green");
    colorChoices.Add("Yellow");
    colorChoices.Add("Purple");
    colorChoices.Add("Pink");
    colorChoices.Add("Cyan");
    colorChoices.Add("Light Grey");

    for (auto& graph : mathData->graphData.graphs)
    {
        auto* nameText = new wxStaticText(scrollPanel, wxID_ANY, graph->GetName());
        auto* colorChoice = new wxChoice(scrollPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
            colorChoices, 0u, wxDefaultValidator, graph->GetName());
        auto* deleteButton = new wxButton(scrollPanel, NewControlId(), "Delete");

        colorChoice->SetStringSelection(graph->GetPen().GetColour().GetAsString().ToStdString());

        gridSizer->Add(nameText, 0u, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 10u);
        gridSizer->Add(colorChoice, 0u, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 10u);
        gridSizer->Add(deleteButton, 0u, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 10u);

        functionWidgets.emplace(deleteButton->GetId(), std::make_tuple(nameText, colorChoice, deleteButton));

        colorChoice->Bind(wxEVT_CHOICE, &GraphFunctionsWindow::OnSelectColor, this);
        deleteButton->Bind(wxEVT_LEFT_DOWN, &GraphFunctionsWindow::OnDeleteFunction, this);
    }

    scrollPanel->SetSizer(gridSizer);

    scrollPanel->FitInside();
    scrollPanel->SetScrollRate(10u, 10u);

    topSizer->AddSpacer(5u);
    topSizer->Add(labelSizer, 0u);
    topSizer->Add(scrollPanel, 0u, wxEXPAND | wxALL);
    topSizer->AddSpacer(5u);

    topSizer->Fit(this);
    topSizer->SetSizeHints(this);

    SetSizer(topSizer);
}

void GraphFunctionsWindow::OnDeleteFunction(wxMouseEvent & event)
{
    auto& widgetGroup = this->functionWidgets.at(event.GetId());

    auto& deletedLayer = std::find_if(std::begin(this->mathData->graphData.graphs), std::end(this->mathData->graphData.graphs),
        [&widgetGroup](const auto & graph) { return graph->GetName().ToStdString() == std::get<0>(widgetGroup)->GetLabel().ToStdString(); });

    this->mathData->graphData.plotWindow->DelLayer(*deletedLayer, true);

    this->mathData->graphData.graphs.erase(deletedLayer);

    std::get<0>(widgetGroup)->Destroy();
    std::get<1>(widgetGroup)->Destroy();
    std::get<2>(widgetGroup)->Destroy();

    this->Layout();
}

void GraphFunctionsWindow::OnSelectColor(wxCommandEvent & event)
{
    auto* colorChoice = dynamic_cast<wxChoice*>(event.GetEventObject());

    auto& graph = std::find_if(std::begin(this->mathData->graphData.graphs), std::end(this->mathData->graphData.graphs),
        [&colorChoice](const auto & graph) { return graph->GetName() == colorChoice->GetName(); });

    (*graph)->SetPen(wxPen(wxColor(colorChoice->GetStringSelection())));

    this->mathData->graphData.plotWindow->UpdateAll();
}