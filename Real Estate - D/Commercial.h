#pragma once
#include "Property.h"
class Commercial :
	public Property
{
public:
	Commercial(int id, string address, int value, bool isRental, bool discountedTaxes, double discountRate);
	~Commercial();

	string toString() override;
	double TaxesDue() override;

	static Commercial* Commercial::LoadCommercial(int& id, istream& inputStream);

	static const string CommercialTag;

private:
	bool _discountedTaxes;
	double _discountRate;

	static const double RentalTaxRate;
	static const double NonRentalTaxRate;
};

