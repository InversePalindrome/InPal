/*
Copyright (c) 2017 InversePalindrome
InPal - Window.cpp
InversePalindrome.com
*/


#include "MainWindow.hpp"
#include "TabBar.hpp"
#include "AddVariableWindow.hpp"
#include "AddConstantWindow.hpp"
#include "AddFunctionWindow.hpp"
#include "ModifyVariablesWindow.hpp"
#include "ModifyConstantsWindow.hpp"
#include "ModifyFunctionsWindow.hpp"


MainWindow::MainWindow(const std::string& title, MathData<double>* mathData) :
	wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(720u, 640u)),
	mathData(mathData)
{
	CenterOnScreen();

	SetBackgroundColour(wxColor(105u, 105u, 105u));
	SetIcon(wxIcon("Resources/Images/InversePalindromeIcon.ico", wxBITMAP_TYPE_ICO));

	new TabBar(this, mathData);

	auto* addMenu = new wxMenu("Add");

	addMenu->Append(new wxMenuItem(addMenu, wxNewId(), "Variable"));
	addMenu->Append(new wxMenuItem(addMenu, wxNewId(), "Constant"));
	addMenu->Append(new wxMenuItem(addMenu, wxNewId(), "Function"));

	auto* modifyMenu = new wxMenu("Modify");

	modifyMenu->Append(new wxMenuItem(modifyMenu, wxNewId(), "Variables"));
	modifyMenu->Append(new wxMenuItem(modifyMenu, wxNewId(), "Constants"));
	modifyMenu->Append(new wxMenuItem(modifyMenu, wxNewId(), "Functions"));

	auto* menuBar = new wxMenuBar();

	menuBar->Append(addMenu, addMenu->GetTitle());
	menuBar->Append(modifyMenu, modifyMenu->GetTitle());
	
	SetMenuBar(menuBar);

	addMenu->Bind(wxEVT_MENU, &MainWindow::OnAddVariable, this, addMenu->FindItemByPosition(0u)->GetId());
	addMenu->Bind(wxEVT_MENU, &MainWindow::OnAddConstant, this, addMenu->FindItemByPosition(1u)->GetId());
	addMenu->Bind(wxEVT_MENU, &MainWindow::OnAddFunction, this, addMenu->FindItemByPosition(2u)->GetId());

	modifyMenu->Bind(wxEVT_MENU, &MainWindow::OnModifyVariables, this, modifyMenu->FindItemByPosition(0u)->GetId());
	modifyMenu->Bind(wxEVT_MENU, &MainWindow::OnModifyConstants, this, modifyMenu->FindItemByPosition(1u)->GetId());
	modifyMenu->Bind(wxEVT_MENU, &MainWindow::OnModifyFunctions, this, modifyMenu->FindItemByPosition(2u)->GetId());
}


void MainWindow::OnAddVariable(wxCommandEvent& event)
{
	auto* addVariableWindow = new AddVariableWindow(this, this->mathData);

	addVariableWindow->Show(true);
}

void MainWindow::OnAddConstant(wxCommandEvent& event)
{
	auto* addConstantWindow = new AddConstantWindow(this, this->mathData);

	addConstantWindow->Show(true);
}

void MainWindow::OnAddFunction(wxCommandEvent& event)
{
	auto* addFunctionWindow = new AddFunctionWindow(this, this->mathData);

	addFunctionWindow->Show(true);
}

void MainWindow::OnModifyVariables(wxCommandEvent& event)
{
	auto* modifyVariablesWindow = new ModifyVariablesWindow(this, this->mathData);

	modifyVariablesWindow->Show(true);
}

void MainWindow::OnModifyConstants(wxCommandEvent& event)
{
	auto* modifyConstantsWindow = new ModifyConstantsWindow(this, this->mathData);

	modifyConstantsWindow->Show(true);
}

void MainWindow::OnModifyFunctions(wxCommandEvent& event)
{
	auto* modifyFunctionsWindow = new ModifyFunctionsWindow(this, this->mathData);

	modifyFunctionsWindow->Show(true);
}