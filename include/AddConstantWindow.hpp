/*
Copyright (c) 2017 InversePalindrome
InPal - AddConstantWindow.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/minifram.h>
#include <wx/textctrl.h>


class AddConstantWindow : public wxMiniFrame
{
public:
    AddConstantWindow(wxWindow* parent, MathDataDefault* mathData);

private:
    MathDataDefault* mathData;

    wxTextCtrl* nameEntry;
    wxTextCtrl* valueEntry;

    void OnAddConstant(wxMouseEvent& event);
};