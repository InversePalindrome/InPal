#/*
Copyright (c) 2017 InversePalindrome
InPal - GraphSettingsWindow.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/minifram.h>
#include <wx/textctrl.h>


class GraphSettingsWindow : public wxMiniFrame
{
public:
	GraphSettingsWindow(wxWindow* parent, MathData<double>* mathData);

private:
	MathData<double>* mathData;

	wxTextCtrl* minXEntry;
	wxTextCtrl* maxXEntry;

	void OnUpdate(wxMouseEvent& event);
};