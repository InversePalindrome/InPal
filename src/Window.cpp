/*
Copyright (c) 2017 InversePalindrome
InPal - Window.cpp
InversePalindrome.com
*/


#include "Window.hpp"
#include "MainPanel.hpp"


Window::Window(const std::string& title) :
	wxFrame(nullptr, wxID_ANY, title, wxPoint(200u, 20u), wxSize(720u, 640u))
{
	auto* mainPanel = new MainPanel(this);

	auto* addMenu = new wxMenu("Add");

	addMenu->Append(0u, "Variable");
	addMenu->Append(1u, "Constant");
	addMenu->Append(2u, "Function");

	auto* menuBar = new wxMenuBar();

	menuBar->Append(addMenu, addMenu->GetTitle());
	
	//menuBar->Bind(wxEVT_MENU, )
	SetMenuBar(menuBar);

	SetBackgroundColour(wxColor(192u, 197u, 206u));
	SetIcon(wxIcon("Resources/Images/InversePalindromeIcon.ico", wxBITMAP_TYPE_ICO));
}