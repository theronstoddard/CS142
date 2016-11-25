#pragma once
#include "Property.h"
#include <vector>

class Residential :	public Property
{
public:
	Residential(int id, string address, int value, bool isRental, bool isOccupied);
	string toString() override;
	double TaxesDue() override;

	static Residential* Residential::LoadResidential(int& id, istream& inputStream);

	~Residential();

	static const string ResidentialTag;

private:
	bool _isOccupied;

	static const double OccupiedTaxRate;
	static const double UnoccupiedTaxRate;
};

