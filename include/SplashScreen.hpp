/*
Copyright (c) 2017 InversePalindrome
InPal - SplashScreen.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/splash.h>


class SplashScreen : public wxSplashScreen
{
public:
    SplashScreen(const wxBitmap& bitmap, std::size_t activeTime, MathDataDefault* mathData);

private:
    MathDataDefault* mathData;

    void OnCloseWindow(wxCloseEvent& event);
};