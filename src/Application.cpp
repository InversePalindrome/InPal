/*
Copyright (c) 2017 InversePalindrome
InPal - Application.cpp
InversePalindrome.com
*/


#include "Application.hpp"
#include "Window.hpp"


bool Application::OnInit()
{
	auto* window = new Window("Inverse Palindrome");

	window->Show(true);

	return true;
}