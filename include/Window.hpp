/*
Copyright (c) 2017 InversePalindrome
InPal - Window.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/frame.h>
#include <wx/menu.h>


class Window : public wxFrame
{
public:
    Window(const std::string& title);

private:
    MathData<double> mathData;

    void OnAddVariable(wxCommandEvent& event);
    void OnAddConstant(wxCommandEvent& event);
    void OnAddFunction(wxCommandEvent& event);

    void OnModifyVariables(wxCommandEvent& event);
    void OnModifyConstants(wxCommandEvent& event);
    void OnModifyFunctions(wxCommandEvent& event);
};