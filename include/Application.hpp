/*
Copyright (c) 2017 InversePalindrome
InPal - Application.hpp
InversePalindrome.com
*/


#pragma once

#include <wx/app.h>
#include <wx/wxprec.h>


class Application : public wxApp
{
public:
	virtual bool OnInit() override;
};

wxIMPLEMENT_APP(Application);