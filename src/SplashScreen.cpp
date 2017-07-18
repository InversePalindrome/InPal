/*
Copyright (c) 2017 InversePalindrome
InPal - SplashScreen.cpp
InversePalindrome.com
*/


#include "SplashScreen.hpp"
#include "MainWindow.hpp"


SplashScreen::SplashScreen(const wxBitmap& bitmap, std::size_t activeTime, MathData<double>* mathData) :
	wxSplashScreen(bitmap, wxSPLASH_TIMEOUT | wxSPLASH_CENTRE_ON_SCREEN, activeTime, nullptr, wxID_ANY, wxDefaultPosition, wxSize(720u, 640u), wxDEFAULT_FRAME_STYLE),
	mathData(mathData)
{
	Bind(wxEVT_CLOSE_WINDOW, &SplashScreen::OnCloseWindow, this);
}

void SplashScreen::OnCloseWindow(wxCloseEvent& event)
{
	auto* mainWindow = new MainWindow("InversePalindrome", this->mathData);

	mainWindow->Show(true);

	this->Destroy();
}