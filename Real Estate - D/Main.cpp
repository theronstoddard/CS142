#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include "Property.h"
#include "Residential.h"
#include "Commercial.h"
#include "InvalidInputException.h"

using namespace std;

#pragma region Declarations

int Menu(int propertiesCount);
bool LoadFile(vector<Property*>& properties);
void ClearProperties(vector<Property*>& properties);
void DisplayProperties(vector<Property*>& properties);
void ComputeTaxes(vector<Property*>& properties);
void ComputeTaxesFormatted(vector<Property*>& properties);
void SortByAddress(vector<Property*>& properties);
void SortByTaxesDue(vector<Property*>& properties);
int GetLongestStringLength(vector<Property*>& properties);

const int LOAD_DATA_FILE_OPTION = 1;
const int COMPUTE_TAXES_OPTION = 2;
const int SORT_BY_ADDRESS_OPTION = 3;
const int SORT_BY_TAXES_DUE_OPTION = 4;
const int QUIT_PROGRAM_OPTION = 5;
const int QUIT_PROGRAM_OPTION_NO_DATA = 2;

#pragma endregion


int main()
{
	vector<Property*> properties;
	int option = 0;

	do
	{
		option = Menu(properties.size());
		if (option == LOAD_DATA_FILE_OPTION)
		{
			ClearProperties(properties);
			if (!LoadFile(properties))
				option = QUIT_PROGRAM_OPTION;
			else
				DisplayProperties(properties);
		}
		else if (option == COMPUTE_TAXES_OPTION)
			ComputeTaxesFormatted(properties);
		else if (option == SORT_BY_ADDRESS_OPTION)
		{
			SortByAddress(properties);
			ComputeTaxesFormatted(properties);
		}
		else if (option == SORT_BY_TAXES_DUE_OPTION)
		{
			SortByTaxesDue(properties);
			ComputeTaxesFormatted(properties);
		}
	} while (option != QUIT_PROGRAM_OPTION);

	system("pause");
	return 0;
}

bool LoadFile(vector<Property*>& properties)
{
	int id = 0;
	string fileName;
	string propertyType;
	Property* property;
	string invalidInput;
	string errorMessage;

	cout << endl << "Enter file name: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, fileName);
	cout << endl;
	//fileName = "MyTest.txt";

	ifstream inputFile(fileName);
	if (!inputFile)
	{
		cout << "File " << fileName << " doesn't exist. Quitting." << endl;
		return false;
	}

	while (!inputFile.fail() && !inputFile.eof())
	{
		string inputLine;
		getline(inputFile, inputLine);
		istringstream inputLineStream(inputLine);

		try
		{
			inputLineStream >> propertyType;

			if (propertyType == Residential::ResidentialTag)
				property = Residential::LoadResidential(id, inputLineStream);
			else if (propertyType == Commercial::CommercialTag)
				property = Commercial::LoadCommercial(id, inputLineStream);
			else
			{
				throw InvalidInputException();
			}

			properties.push_back(property);						
		}
		catch (const InvalidInputException& exception)
		{
			cout << "Ignoring bad " << propertyType << " in input file: " << inputLine << endl;
		}
	}

	inputFile.close();
	return true;
}

void ClearProperties(vector<Property*>& properties)
{
	while (properties.size() > 0)
	{
		delete properties[0];
		properties.erase(properties.begin());
	}
}


void DisplayProperties(vector<Property*>& properties)
{
	cout << endl << "All valid properties:" << endl;
	for (int i = 0; i < properties.size(); i++)
	{
		cout << properties[i]->toString();
	}
	cout << endl;
}

void ComputeTaxes(vector<Property*>& properties)
{
	Property* pProperty;
	cout << endl << "NOW PRINTING TAX REPORT:" << endl;
	double value;

	for (int i = 0; i < properties.size(); i++)
	{
		cout << "** Taxes due for the property at: " << properties[i]->getAddress() << endl;

		cout << setw(48) << left << "\tProperty id:";
		cout << "\t" << properties[i]->getId() << endl;

		cout << setw(48) << left << "\tThis property has an estimated value of:";
		cout << "\t" << properties[i]->getValue() << endl;

		cout << setw(48) << left << "\tTaxes due on this property are:";
		cout << "\t" << properties[i]->TaxesDue() << endl;
	}
	cout << endl;
}

void ComputeTaxesFormatted(vector<Property*>& properties)
{
	Property* pProperty;
	long double value;
	int longestString;
	cout.imbue(locale("en-US"));
	cout << endl << "NOW PRINTING TAX REPORT:" << endl;

	longestString = GetLongestStringLength(properties);
	for (int i = 0; i < properties.size(); i++)
	{
		cout << "** Taxes due for the property at: " << properties[i]->getAddress() << endl;

		cout << setw(48) << left << "\tProperty id:";
		cout << "\t" << properties[i]->getId() << endl;

		cout << setw(48) << left << "\tThis property has an estimated value of:";

		value = properties[i]->getValue() * static_cast<long double>(100);
		cout << "\t" << setw(longestString) << std::right << showbase << put_money(value) << endl;

		cout << setw(48) << left << "\tTaxes due on this property are:";
		value = properties[i]->TaxesDue() * static_cast<long double>(100);
		cout << "\t" << setw(longestString) << std::right << showbase << put_money(value) << endl;
	}
	cout << endl;
}

int GetMoneyAsStringLength(long double value)
{
	stringstream ss;
	ss.imbue(locale("en-US"));

	ss << showbase << put_money(value);	
	string strValue = ss.str();

	return strValue.length();
}

int GetLongestStringLength(vector<Property*>& properties)
{
	int longest = 0;
	int valueLength;
	long double value;

	for (int i = 0; i < properties.size(); i++)
	{
		value = properties[i]->getValue() * static_cast<long double>(100);
		valueLength = GetMoneyAsStringLength(value);
		if (valueLength > longest)
		{
			longest = valueLength;
		}
		value = properties[i]->TaxesDue() * static_cast<long double>(100);
		valueLength = GetMoneyAsStringLength(value);
		if (valueLength > longest)
		{
			longest = valueLength;
		}
	}

	return longest;
}


// Use Shell Sort to sort properties by address
void SortByAddress(vector<Property*>& properties)
{
	Property* pTemp;
	bool swapOccurred = true;
	int compareDistance = properties.size();

	while (swapOccurred || (compareDistance > 1))
	{
		swapOccurred = false;
		compareDistance = (compareDistance + 1) / 2;
		for (int i = 0; i < (properties.size() - compareDistance); i++)
		{
			// if position[d+i] is less than or equal to i, swap positions d+i and i
			if (properties[i]->getAddress().compare(properties[i + compareDistance]->getAddress()) > 0)
			{
				pTemp = properties[i + compareDistance];
				properties[i + compareDistance] = properties[i];
				properties[i] = pTemp;
				swapOccurred = true;
			}
		}
	}
}

// Use Shell Sort to sort properties by address
void SortByTaxesDue(vector<Property*>& properties)
{
	Property* pTemp;
	bool swapOccurred = true;
	int compareDistance = properties.size();

	while (swapOccurred || (compareDistance > 1))
	{
		swapOccurred = false;
		compareDistance = (compareDistance + 1) / 2;
		for (int i = 0; i < (properties.size() - compareDistance); i++)
		{
			// if position[d+i] is greater than i, swap positions d+i and i
			if (properties[i + compareDistance]->TaxesDue() <= properties[i]->TaxesDue())
			{
				pTemp = properties[i + compareDistance];
				properties[i + compareDistance] = properties[i];
				properties[i] = pTemp;
				swapOccurred = true;
			}
		}
	}
}

#pragma region Menu

int Menu(int propertiesCount)
{
	int option = 0;
	bool invalidChoice = false;
	int QuitProgramOption = QUIT_PROGRAM_OPTION;

	cout << endl;
	cout << "1 - Load Data File" << endl;
	if (propertiesCount > 0)
	{
		cout << "2 - Calculate Taxes" << endl;
		cout << "3 - Sort by Address" << endl;
		cout << "4 - Sort by Taxes Due" << endl;		
		cout << "5 - Quit Program" << endl;
	}
	else
	{
		cout << "2 - Quit Program" << endl;
		QuitProgramOption = QUIT_PROGRAM_OPTION_NO_DATA;
	}

	do
	{
		cout << "Enter your selection now: ";
		cin >> option;
		invalidChoice = cin.fail() || option < LOAD_DATA_FILE_OPTION || option > QuitProgramOption;

		if (invalidChoice)
		{
			cout << "INVALID SELECTION.  Please enter 1-5." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (invalidChoice);

	if (propertiesCount == 0 && option == QUIT_PROGRAM_OPTION_NO_DATA)
	{
		option = QUIT_PROGRAM_OPTION;
	}

	return option;
}

#pragma endregion 
