#include "Commercial.h"

const string Commercial::CommercialTag = "Commercial";
const double Commercial::RentalTaxRate = 0.012;
const double Commercial::NonRentalTaxRate = 0.01;

Commercial::Commercial(int id, string address, int value, bool isRental, bool discountedTaxes, double discountRate)
	: Property(id, address, value, isRental)
{
	_discountedTaxes = discountedTaxes;
	_discountRate = discountRate;
}


Commercial::~Commercial()
{
}

string Commercial::toString()
{
	stringstream ss;

	ss << "Property id: " << Id << ", ";
	ss << "Address: " << Address << ", ";
	ss << (IsRental ? "Rental" : "NOT rental") << ", ";
	ss << "Estimated value: " << Value << ", ";
	ss << (_discountedTaxes ? "Discounted" : "NOT discounted");
	if (_discountedTaxes)
	{
		ss << ", Discount: " << _discountRate;		
	}
	ss << endl;

	return ss.str();
}

double Commercial::TaxesDue()
{
	double taxableValue = Value;
	if (_discountedTaxes)
	{
		taxableValue = Value - (Value * _discountRate);
	}

	return taxableValue * (IsRental ? RentalTaxRate : NonRentalTaxRate);
}

Commercial* Commercial::LoadCommercial(int& id, istream& inputStream)
{
	bool isRental;
	int propertyValue;
	bool discountedTaxes;
	double discountRate;
	string address;
	Commercial* pCommercial;

	isRental = GetBooleanInput(inputStream);
	propertyValue = GetIntInput(inputStream);
	discountedTaxes = GetBooleanInput(inputStream);
	discountRate = GetDoubleInput(inputStream);
	inputStream >> ws;
	getline(inputStream, address);

	pCommercial = new Commercial(id++, address, propertyValue, isRental, discountedTaxes, discountRate);

	return pCommercial;
}

