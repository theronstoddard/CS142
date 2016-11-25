#pragma once
#include <string>
#include "vcruntime_exception.h"

class InvalidInputException : public std::exception
{
public:

	InvalidInputException()
	{}

	InvalidInputException(string message)
	{
		Message = message;
	}

	~InvalidInputException()
	{
	}

	string Message;
};

