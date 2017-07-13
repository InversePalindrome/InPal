/*
Copyright (c) 2017 InversePalindrome
InPal - Window.cpp
InversePalindrome.com
*/


#include "Window.hpp"
#include "MainPanel.hpp"
#include "AddVariableWindow.hpp"
#include "AddConstantWindow.hpp"
#include "AddFunctionWindow.hpp"


Window::Window(const std::string& title) :
	wxFrame(nullptr, wxID_ANY, title, wxPoint(200u, 20u), wxSize(720u, 640u)),
	mathData()
{
	auto* mainPanel = new MainPanel(this, &mathData);

	auto* addMenu = new wxMenu("Add");

	addMenu->Append(new wxMenuItem(addMenu, 0u, "Variable"));
	addMenu->Append(new wxMenuItem(addMenu, 1u, "Constant"));
	addMenu->Append(new wxMenuItem(addMenu, 2u, "Function"));

	auto* menuBar = new wxMenuBar();

	menuBar->Append(addMenu, addMenu->GetTitle());
	
	addMenu->Bind(wxEVT_MENU, &Window::OnAddVariable, this, 0u);
	addMenu->Bind(wxEVT_MENU, &Window::OnAddConstant, this, 1u);
	addMenu->Bind(wxEVT_MENU, &Window::OnAddFunction, this, 2u);

	SetMenuBar(menuBar);

	SetBackgroundColour(wxColor(192u, 197u, 206u));
	SetIcon(wxIcon("Resources/Images/InversePalindromeIcon.ico", wxBITMAP_TYPE_ICO));
}


void Window::OnAddVariable(wxCommandEvent& event)
{
	auto* addVariableWindow = new AddVariableWindow(this, &this->mathData);

	addVariableWindow->Show(true);
}

void Window::OnAddConstant(wxCommandEvent& event)
{
	auto* addConstantWindow = new AddConstantWindow(this, &this->mathData);

	addConstantWindow->Show(true);
}

void Window::OnAddFunction(wxCommandEvent& event)
{
	auto* addFunctionWindow = new AddFunctionWindow(this, &this->mathData);

	addFunctionWindow->Show(true);
}