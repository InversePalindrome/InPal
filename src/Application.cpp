/*
Copyright (c) 2017 InversePalindrome
InPal - Application.cpp
InversePalindrome.com
*/


#include "Application.hpp"
#include "SplashScreen.hpp"

#include <boost/algorithm/string.hpp>
#include <fstream>


bool Application::OnInit() 
{
	wxInitAllImageHandlers();

	loadData();

	new SplashScreen(wxBitmap("Resources/Images/InversePalindromeLogo.png", wxBITMAP_TYPE_PNG), 2500u, &mathData);

	return true;
}

int Application::OnExit()
{
	this->saveData();

	return 0;
}

void Application::loadData()
{
	std::ifstream inFile("Resources/Files/Variables.txt");

	std::string name;
	double value;

	while (inFile >> name >> value)
	{
		this->mathData.variables[name] = value;
		this->mathData.mathSolver.addVariable(name, this->mathData.variables.at(name));
	}

	inFile.close();
	inFile.clear();

	inFile.open("Resources/Files/Constants.txt");

	while(inFile >> name >> value)
	{
		this->mathData.constants[name] = value;
		this->mathData.mathSolver.addConstant(name, this->mathData.constants.at(name));
	}

	inFile.close();
	inFile.clear();

	inFile.open("Resources/Files/Functions.txt");

	std::string category;
	std::string line;
	std::string parameters;
	std::string body;

	while (std::getline(inFile, line))
	{
		if (line == "Name")
		{
			category = "Name";
			continue;
		}
		else if (line == "Parameters")
		{
			category = "Parameters";
			continue;
		}
		else if (line == "Body")
		{
			category = "Body";
			continue;
		}
		else if (line == "END")
		{
			this->mathData.functions[name] = std::make_pair(parameters, body);

			std::vector<std::string> parameterTokens;

			boost::split(parameterTokens, parameters, boost::is_any_of(", "));

			this->mathData.mathSolver.addCompositorFunction(name, parameterTokens, body);

			body.clear();
			
			continue;
		}

		if (category == "Name")
		{
			name = line;
		}
		else if (category == "Parameters")
		{
			parameters = line;
		}
		else if (category == "Body")
		{
			body += line + '\n';
		}
	}
}

void Application::saveData()
{
	std::ofstream outFile("Resources/Files/Variables.txt");

	for (const auto& variable : this->mathData.variables)
	{
		outFile << variable.first << " " <<  variable.second << '\n';
	}

	outFile.close();
	outFile.clear();

	outFile.open("Resources/Files/Constants.txt");

	for (const auto& constant : this->mathData.constants)
	{
		outFile << constant.first << " " <<  constant.second << '\n';
	}

	outFile.close();
	outFile.clear();

	outFile.open("Resources/Files/Functions.txt");

	for (const auto& function : this->mathData.functions)
	{
		outFile << "Name" << '\n' << function.first << '\n' << "Parameters" <<'\n' << function.second.first << '\n' << "Body" << '\n' << function.second.second << '\n' << "END" << '\n';
	}
}

