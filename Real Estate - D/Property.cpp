#include "Property.h"
#include "InvalidInputException.h"


Property::Property(int id, string address, int value, bool isRental)
{
	Id = id;
	Address = address;
	Value = value;
	IsRental = isRental;
}


Property::~Property()
{
}

string Property::getAddress() const
{
	return Address;
}

int Property::getValue() const
{
	return Value;
}

int Property::getId() const
{
	return Id;
}

int Property::GetIntInput(istream& inputStream)
{
	int input;
	inputStream >> input;

	if (inputStream.fail())
	{
		inputStream.clear();
		throw InvalidInputException();
	}

	return  input;
}

double Property::GetDoubleInput(istream& inputStream)
{
	double input;
	inputStream >> input;

	if (inputStream.fail())
	{
		inputStream.clear();
		throw InvalidInputException();
	}

	return  input;
}

bool Property::GetBooleanInput(istream& inputStream)
{
	bool input;
	inputStream >> input;

	if (inputStream.fail())
	{
		inputStream.clear();
		throw InvalidInputException();
	}

	return  input;

}
