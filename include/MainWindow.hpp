/*
Copyright (c) 2017 InversePalindrome
InPal - Window.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/frame.h>
#include <wx/menu.h>


class MainWindow : public wxFrame
{
public:
    MainWindow(const std::string& title, MathDataDefault* mathData);

private:
    MathDataDefault* mathData;

    void OnAddVariable(wxCommandEvent& event);
    void OnAddConstant(wxCommandEvent& event);
    void OnAddFunction(wxCommandEvent& event);

    void OnModifyVariables(wxCommandEvent& event);
    void OnModifyConstants(wxCommandEvent& event);
    void OnModifyFunctions(wxCommandEvent& event);

    void OnGraphSettings(wxCommandEvent& event);
    void OnGraphFunctions(wxCommandEvent& event);
};