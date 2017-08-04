#/*
Copyright (c) 2017 InversePalindrome
InPal - GraphSettingsWindow.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/minifram.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>


class GraphSettingsWindow : public wxMiniFrame
{
public:
	GraphSettingsWindow(wxWindow* parent, MathDataDefault* mathData);

private:
	MathDataDefault* mathData;

	wxTextCtrl* minXEntry;
	wxTextCtrl* maxXEntry;
	wxChoice* typeChoice;

	void OnUpdate(wxMouseEvent& event);
};