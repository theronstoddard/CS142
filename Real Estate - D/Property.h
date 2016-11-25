#pragma once
#include <string>
#include <sstream>

using namespace std;

class Property
{
public:
	Property(int id, string address, int value, bool isRental);
	virtual ~Property();

	virtual string toString() = 0;
	virtual double TaxesDue() = 0;
	string getAddress() const;
	int getValue() const;
	int getId() const;

	static int Property::GetIntInput(istream& inputStream);
	static double Property::GetDoubleInput(istream& inputStream);
	static bool Property::GetBooleanInput(istream& inputStream);

protected:
	int Id;
	string Address;
	int Value;
	bool IsRental;
};

