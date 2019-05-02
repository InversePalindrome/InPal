/*
Copyright (c) 2017 InversePalindrome
InPal - GraphFunctionsWindow.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/minifram.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/button.h>

#include <tuple>
#include <string>
#include <unordered_map>


class GraphFunctionsWindow : public wxMiniFrame
{
public:
    GraphFunctionsWindow(wxWindow* parent, MathDataDefault* mathData);

private:
    MathDataDefault* mathData;

    std::unordered_map<std::size_t, std::tuple<wxStaticText*, wxChoice*, wxButton*>> functionWidgets;

    void OnDeleteFunction(wxMouseEvent& event);
    void OnSelectColor(wxCommandEvent& event);
};