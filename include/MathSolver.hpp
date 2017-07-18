/*
Copyright (c) 2017 InversePalindrome
InPal - MathSolver.hpp
InversePalindrome.com
*/


#pragma once

#include "Exprtk.hpp"
#include "GCD.hpp"
#include "LCM.hpp"
#include "PrimeTest.hpp"

#include <iostream>


template<typename T>
class MathSolver
{
public:
	MathSolver();
	MathSolver(const std::string& task);

	bool solve();

	T getValue() const;
	std::string getTask() const;

	T getVariable(const std::string& variableName);
	std::string getStringVariable(const std::string& variableName);

	void setTask(const std::string& task);

	void addVariable(const std::string& variableName, T& variable);
	void addConstant(const std::string& constantName, T& constant);
	void addStringVar(const std::string& stringVariableName, std::string& variable);
	void addFunction(const std::string& functionName, exprtk::ifunction<T>& function);
	void addCompositorFunction(const std::string& functionName, const std::vector<std::string>& parameters, const std::string& functionBody);

	void removeVariable(const std::string& variableName);
	void removeStringVar(const std::string& stringVariableName);
	void removeFunction(const std::string& functionName);

	void clearTask();
	void clearSymbols();

private:
	exprtk::parser<T> parser;
	exprtk::expression<T> expression;
	exprtk::symbol_table<T> symbolTable;
	exprtk::function_compositor<T> compositor;

	exprtk::parser_error::type error;

	std::string task;

	GCD<T> gcd;
	LCM<T> lcm;
	PrimeTest<T> primeTest;

	void loadConstants();
	void loadFunctions();
};


template<typename T>
MathSolver<T>::MathSolver() :
	MathSolver("")
{
}

template<typename T>
MathSolver<T>::MathSolver(const std::string& task) :
	parser(),
	expression(),
	symbolTable(),
	compositor(symbolTable),
	task(task),
	error()
{
	expression.register_symbol_table(symbolTable);

	loadConstants();
	loadFunctions();
}

template<typename T>
bool MathSolver<T>::solve()
{
	if (!this->parser.compile(this->task, this->expression))
	{
		for (std::size_t i = 0; i < this->parser.error_count(); ++i)
		{
			this->error = this->parser.get_error(i);

			std::cerr << "Error: " << i << " [LINE]: " << this->error.line_no << " [COL]: " << this->error.column_no << " [POS]: " << this->error.token.position
				<< " Type: " << exprtk::parser_error::to_str(this->error.mode).c_str() << " Message: " << this->error.diagnostic.c_str() << "\n";
		}

		return false;
	}

	return true;
}

template<typename T>
T MathSolver<T>::getValue() const
{
	return this->expression.value();
}

template<typename T>
std::string MathSolver<T>::getTask() const
{
	return this->task;
}

template<typename T>
T MathSolver<T>::getVariable(const std::string& variableName)
{
	return this->symbolTable.get_variable(variableName)->ref();
}

template<typename T>
std::string MathSolver<T>::getStringVariable(const std::string& variableName)
{
	return this->symbolTable.get_stringvar(variableName)->value();
}

template<typename T>
void MathSolver<T>::setTask(const std::string& task)
{
	this->task = task;
}

template<typename T>
void MathSolver<T>::addVariable(const std::string& variableName, T& variable)
{
	this->symbolTable.add_variable(variableName, variable);
}

template<typename T>
void MathSolver<T>::addConstant(const std::string& constantName, T& variable)
{
	this->symbolTable.add_constant(constantName, variable);
}

template<typename T>
void MathSolver<T>::addStringVar(const std::string& stringVariableName, std::string& variable)
{
	this->symbolTable.add_stringvar(stringVariableName, variable);
}

template<typename T>
void MathSolver<T>::addFunction(const std::string& functionName, exprtk::ifunction<T>& function)
{
	this->symbolTable.add_function(functionName, function);
}

template<typename T>
void MathSolver<T>::addCompositorFunction(const std::string& functionName, const std::vector<std::string>& parameters, const std::string& functionBody)
{
	exprtk::function_compositor<T>::function function(functionName, functionBody);

	for (const auto& parameter : parameters)
	{
		function.var(parameter);
	}

	this->compositor.add(function, true);
}

template<typename T>
void MathSolver<T>::removeVariable(const std::string& variableName)
{
	this->symbolTable.remove_variable(variableName);
}

template<typename T>
void MathSolver<T>::removeStringVar(const std::string& stringVariableName)
{
	this->symbolTable.remove_stringvar(stringVariableName);
}

template<typename T>
void MathSolver<T>::removeFunction(const std::string& functionName)
{
	this->symbolTable.remove_function(functionName);
}

template<typename T>
void MathSolver<T>::clearTask()
{
	this->task.clear();
}

template<typename T>
void MathSolver<T>::clearSymbols()
{
	this->symbolTable.clear();
}

template<typename T>
void MathSolver<T>::loadConstants()
{
	this->symbolTable.add_constants();
	this->symbolTable.add_constant("e", 2.7182818284590452353602874713527);
}

template<typename T>
void MathSolver<T>::loadFunctions()
{
	this->symbolTable.add_function("gcd", this->gcd);
	this->symbolTable.add_function("lcm", this->lcm);
	this->symbolTable.add_function("is_prime", this->primeTest);
}
