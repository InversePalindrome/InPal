/*
Copyright (c) 2017 InversePalindrome
InPal - Application.hpp
InversePalindrome.com
*/


#pragma once

#include "MathData.hpp"

#include <wx/app.h>
#include <wx/wxprec.h>


class Application : public wxApp
{
public:
	virtual bool OnInit() override;
	virtual int OnExit() override;

private:
	MathDataDefault mathData;

	void loadData();
	void saveData();
};

wxIMPLEMENT_APP(Application);