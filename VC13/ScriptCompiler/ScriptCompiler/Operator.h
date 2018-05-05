#pragma once


class Operator
{
public:
	Operator() :scriptCommand(0), precedence(0){}
	Operator(int scriptCommand, int precedence) :scriptCommand(scriptCommand), precedence(precedence){}

	int		scriptCommand;
	int		precedence;
};

