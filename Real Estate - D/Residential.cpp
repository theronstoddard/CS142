#include "Residential.h"
#include <vector>

const string Residential::ResidentialTag = "Residential";
const double Residential::OccupiedTaxRate = 0.006;
const double Residential::UnoccupiedTaxRate = 0.009;

Residential::Residential(int id, string address, int value, bool isRental, bool isOccupied)
	: Property(id, address, value, isRental)
	
{
	_isOccupied = isOccupied;
}


Residential::~Residential()
{
}

string Residential::toString()
{
	stringstream ss;

	ss << "Property id: " << Id << ", ";
	ss << "Address: " << Address << ", ";
	ss << (IsRental ? "Rental" : "NOT rental") << ", ";
	ss << "Estimated value: " << Value << ", ";
	ss << (_isOccupied ? "Occupied" : "NOT occupied") << endl;

	return ss.str();
}

double Residential::TaxesDue()
{
	return Value * (_isOccupied ? OccupiedTaxRate : UnoccupiedTaxRate);
}

Residential* Residential::LoadResidential(int& id, istream& inputStream)
{
	string address;
	bool isRental;
	int propertyValue;
	bool isOccupied;
	Residential* pResidential;

	isRental = GetBooleanInput(inputStream);
	propertyValue = GetIntInput(inputStream);
	isOccupied = GetBooleanInput(inputStream);
	inputStream >> ws;
	getline(inputStream, address);

	pResidential = new Residential(id++, address, propertyValue, isRental, isOccupied);

	return pResidential;
}

