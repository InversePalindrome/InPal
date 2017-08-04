/*
Copyright (c) 2017 InversePalindrome
InPal - CalculusPanel.cpp
InversePalindrome.com
*/


#include "CalculusPanel.hpp"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>

#include <boost/format.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/replace.hpp>


CalculusPanel::CalculusPanel(wxWindow* parent, MathDataDefault* mathData) :
	wxPanel(parent, wxID_ANY),
	mathData(mathData),
	derivativeChoice(),
	derivativeEntry(new wxTextCtrl(this, wxID_ANY)),
	xPositionEntry(new wxTextCtrl(this, wxID_ANY)),
	derivativeSolution(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY)),
	integralEntry(new wxTextCtrl(this, wxID_ANY)),
	initialXEntry(new wxTextCtrl(this, wxID_ANY)),
	finalXEntry(new wxTextCtrl(this, wxID_ANY)),
	integralSolution(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY))
{
	SetBackgroundColour(wxColor(128u, 128u, 128u));

	auto* topSizer = new wxBoxSizer(wxVERTICAL);
	auto* derivativeSizer = new wxBoxSizer(wxHORIZONTAL);
	auto* derivativeButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	auto* integralSizer = new wxBoxSizer(wxHORIZONTAL);
	auto* integralButtonSizer = new wxBoxSizer(wxHORIZONTAL);

	auto* derivativeText = new wxStaticText(this, wxID_ANY, "Derivative");
	auto* derivativeFunctionText = new wxStaticText(this, wxID_ANY, "Function");
	auto* xPositionText = new wxStaticText(this, wxID_ANY, "Position(X):");

	auto* integralText = new wxStaticText(this, wxID_ANY, "Integral");
	auto* integralFunctionText = new wxStaticText(this, wxID_ANY, "Function");
	auto* integralInitialXText = new wxStaticText(this, wxID_ANY, "Starting Position(X):");
	auto* integralFinalXText = new wxStaticText(this, wxID_ANY, "Final Position(X):");

	auto& font = wxFont(8u, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

	derivativeText->SetFont(font);
	xPositionText->SetFont(font);
	derivativeFunctionText->SetFont(font);
	integralText->SetFont(font);
	integralFunctionText->SetFont(font);
	integralInitialXText->SetFont(font);
	integralFinalXText->SetFont(font);

	wxArrayString derivativeChoices;
	derivativeChoices.Add("First Derivative");
	derivativeChoices.Add("Second Derivative");
	derivativeChoices.Add("Third Derivative");

	derivativeChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, derivativeChoices);
	derivativeChoice->SetStringSelection("First Derivative");

	auto* solveDerivativeButton = new wxButton(this, wxID_ANY, "Solve");
	auto* solveIntegralButton = new wxButton(this, wxID_ANY, "Solve");

	auto* clearDerivativeButton = new wxButton(this, wxID_ANY, "Clear");
	auto* clearIntegralButton = new wxButton(this, wxID_ANY, "Clear");

	derivativeSizer->Add(derivativeChoice, 0u, wxALL, 10u);
	derivativeSizer->Add(xPositionText, 0u, wxALL, 10u);
	derivativeSizer->Add(xPositionEntry, 0u, wxALL, 10u);

	derivativeButtonSizer->Add(solveDerivativeButton, 0u, wxALL, 5u);
	derivativeButtonSizer->Add(clearDerivativeButton, 0u, wxALL, 5u);

	integralSizer->Add(integralInitialXText, 0u, wxALL, 10u);
	integralSizer->Add(initialXEntry, 0u, wxALL, 10u);
	integralSizer->Add(integralFinalXText, 0u, wxALL, 10u);
	integralSizer->Add(finalXEntry, 0u, wxALL, 10u);

	integralButtonSizer->Add(solveIntegralButton, 0u, wxALL, 5u);
	integralButtonSizer->Add(clearIntegralButton, 0u, wxALL, 5u);

	topSizer->AddSpacer(55u);
	topSizer->Add(derivativeText, 0u, wxALL, 5u);
	topSizer->Add(derivativeSolution, 0u, wxEXPAND | wxALL, 5u);
	topSizer->Add(derivativeFunctionText, 0u, wxEXPAND | wxALL, 5u);
	topSizer->Add(derivativeEntry, 0u, wxEXPAND | wxALL, 5u);
	topSizer->Add(derivativeSizer, 0u, wxALIGN_CENTER | wxALL, 5u);
	topSizer->Add(derivativeButtonSizer, 0u, wxALIGN_CENTER | wxALL, 5u);
	topSizer->AddSpacer(30u);
	topSizer->Add(integralText, 0u, wxALL, 5u);
	topSizer->Add(integralSolution, 0u, wxEXPAND | wxALL, 5u);
	topSizer->Add(integralFunctionText, 0u, wxEXPAND | wxALL, 5u);
	topSizer->Add(integralEntry, 0u, wxEXPAND | wxALL, 5u);
	topSizer->Add(integralSizer, 0u, wxALIGN_CENTER | wxALL, 5u);
	topSizer->Add(integralButtonSizer, 0u, wxALIGN_CENTER | wxALL, 5u);

	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
	
	SetSizer(topSizer);

	solveDerivativeButton->Bind(wxEVT_LEFT_DOWN, &CalculusPanel::OnSolveDerivative, this);
	solveIntegralButton->Bind(wxEVT_LEFT_DOWN, &CalculusPanel::OnSolveIntegral, this);

	clearDerivativeButton->Bind(wxEVT_LEFT_DOWN, &CalculusPanel::OnClearDerivative, this);
	clearIntegralButton->Bind(wxEVT_LEFT_DOWN, &CalculusPanel::OnClearIntegral, this);
}

void CalculusPanel::OnSolveDerivative(wxMouseEvent& event)
{
	auto& functionEquation = this->derivativeEntry->GetValue().ToStdString();

	boost::replace_all(functionEquation, "x", "derivativeVariable");

	this->mathData->mathSolver.setTask(functionEquation);
	
	long double derivativeVariable;
	try
	{
		derivativeVariable = std::stold(this->xPositionEntry->GetValue().ToStdString());
	}
	catch (const std::invalid_argument& e)
	{
		derivativeVariable = 0;
	}

	this->mathData->mathSolver.addVariable("derivativeVariable", derivativeVariable);

	if (this->mathData->mathSolver.solve())
	{
		long double derivative;

		if (this->derivativeChoice->GetStringSelection() == "First Derivative")
		{
			derivative = this->mathData->mathSolver.getDerivative(derivativeVariable);
		}
		else if (this->derivativeChoice->GetStringSelection() == "Second Derivative")
		{
			derivative = this->mathData->mathSolver.getSecondDerivative(derivativeVariable);
		}
		else if (this->derivativeChoice->GetStringSelection() == "Third Derivative")
		{
			derivative = this->mathData->mathSolver.getThirdDerivative(derivativeVariable);
		}

		auto& result = boost::str(boost::format("%.18f") %
			derivative);

		boost::trim_right_if(result, boost::is_any_of("0"));
		boost::trim_right_if(result, boost::is_any_of("."));

		this->derivativeSolution->SetValue(result);
	}
}

void CalculusPanel::OnSolveIntegral(wxMouseEvent& event)
{
	auto& functionEquation = this->integralEntry->GetValue().ToStdString();

	boost::replace_all(functionEquation, "x", "integralVariable");

	this->mathData->mathSolver.setTask(functionEquation);

	long double integralVariable = 0.0;
	long double initialX;
	long double finalX;

	this->mathData->mathSolver.addVariable("integralVariable", integralVariable);

	try
	{
		initialX = std::stold(this->initialXEntry->GetValue().ToStdString());
		finalX = std::stold(this->finalXEntry->GetValue().ToStdString());
	}
	catch (const std::invalid_argument& e)
	{
		initialX = 0.0;
		finalX = 1.0;
	}

	if (this->mathData->mathSolver.solve())
	{
		auto& result = boost::str(boost::format("%.18f") % 
			this->mathData->mathSolver.getIntegral(integralVariable, initialX, finalX));
		boost::trim_right_if(result, boost::is_any_of("0"));
		boost::trim_right_if(result, boost::is_any_of("."));

		this->integralSolution->SetValue(result);
	}
}

void CalculusPanel::OnClearDerivative(wxMouseEvent& event)
{
	this->derivativeSolution->Clear();
	this->derivativeEntry->Clear();
	this->xPositionEntry->Clear();
}

void CalculusPanel::OnClearIntegral(wxMouseEvent& event)
{
	this->integralSolution->Clear();
	this->integralEntry->Clear();
	this->initialXEntry->Clear();
	this->finalXEntry->Clear();
}