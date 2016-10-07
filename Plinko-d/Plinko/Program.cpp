// Hybrid Car.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int QUIT_OPTION = 0;
const int SINGLE_CHIP_OPTION = 1;
const int MULTIPLE_CHIP_OPTION = 2;
const int ROW_COUNT = 12;
const int MIN_SLOT = 0;
const int MAX_SLOT = 8;

static int Money[MAX_SLOT+1] = { 100, 500, 1000, 0, 10000, 0, 1000, 500, 100 };


int Menu();
void SingleChipDropPrompt();
int SingleChipDrop(double slotNumber, bool print);
void MultipleChipDropPrompt();
void MultipleChipDrop(int chips, double slotNumber, double& winnings);

int main()
{
	int option = 0;

	cout << "Welcome to the plinko simulator!" << endl;
	cout << fixed << setprecision(1);
	// ***** Change to srand(time(0)) before submitting? ******
	srand(0);

	do
	{
		option = Menu();
		if (option == SINGLE_CHIP_OPTION)
		{
			SingleChipDropPrompt();
		}
		else if (option == MULTIPLE_CHIP_OPTION)
		{
			MultipleChipDropPrompt();
		}
		
	} while (option > 0);

	return 0;
}

void MultipleChipDropPrompt()
{
	int chips = 0;
	int slot = 0;
	double winnings = 0.0;

	cout << "*** DROP MULTIPLE CHIPS ***" << endl;
	cout << "How many chips do you want to drop (>0)? ";
	cin >> chips;

	if (chips <= 0)
	{
		cout << "INVALID NUMBER OF CHIPS." << endl;
		return;
	}

	cout << "Which slot do you want to drop the chip in (0-8)? ";
	cin >> slot;

	if (slot < MIN_SLOT || slot > MAX_SLOT)
	{
		cout << "INVALID SLOT." << endl;
		return;
	}

	MultipleChipDrop(chips, slot, winnings);
	
	cout << setprecision(2) << "Total Winnings on " << chips << ": $" << winnings << endl;
	cout << setprecision(2) << "Average winnings per chip: $" << winnings / chips << endl;
	cout << fixed << setprecision(1);
}

void MultipleChipDrop(int chips, double slotNumber, double& winnings)
{
	for (int i = 0; i < chips; i++)
	{
		winnings += SingleChipDrop(slotNumber, false);
	}
}

void SingleChipDropPrompt()
{
	int slot = 0;
	double winnings = 0;

	cout << "*** DROP SINGLE CHIP ***" << endl;
	cout << "Which slot do you want to drop the chip in (0-8)? ";
	cin >> slot;

	if (slot < MIN_SLOT || slot > MAX_SLOT)
	{
		cout << "INVALID SLOT." << endl;
		return;
	}

	winnings = SingleChipDrop(slot, true);
	cout << "WINNINGS: $" << winnings << endl;
}

int SingleChipDrop(double slotNumber, bool print)
{
	if (print)
	{
		cout << "[" << slotNumber << " ";
	}

	for (int i = 0; i < ROW_COUNT; i++)
	{
		if (rand() % 2 < 1)
		{
			slotNumber -= 0.5;
		}
		else
		{
			slotNumber += 0.5;
		}

		if (slotNumber > MAX_SLOT)
		{
			slotNumber = 7.5;
		}
		if (slotNumber < MIN_SLOT)
		{
			slotNumber = 0.5;
		}

		if (print)
		{
			cout << slotNumber;
			if (i < ROW_COUNT-1)
			{
				cout << " ";
			}
		}
	}

	if (print)
	{
		cout << "]" << endl;
	}

	return Money[static_cast<int>(slotNumber)];
}

double CalculatePrizeMoney()
{
	throw new exception("Not implemented");
}

int Menu()
{
	cout << endl << "MENU: Please select one of the following options:" << endl;
	cout << "0 - Quit the program" << endl;
	cout << "1 - Drop a single chip into one slot" << endl;
	cout << "2 - Drop multiple chips into one slot" << endl;

	int option = 0;
	bool invalidChoice = false;
	do
	{
		cout << "Enter your selection now: ";
		cin >> option;
		invalidChoice = cin.fail() || option < QUIT_OPTION || option > MULTIPLE_CHIP_OPTION;

		if (invalidChoice)
		{
			cout << "INVALID SELECTION.  Please enter 0, 1 or 2" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (invalidChoice);

	return option;
}

double _averageValues[MAX_SLOT+1][2] = {
	{ 500, 1000},
	{ 750, 1250},
	{ 1250, 2000},
	{ 2000, 2500},
	{ 2250, 2750},
	{ 2000, 2500 },
	{ 1250, 2000 },
	{ 750, 1250 },
	{ 500, 1000 }
};

int Xmain()
{
	double winnings = 0.0;

	srand(0);
	cout << fixed << setprecision(2);

	// Test single chip drop
	for (int i = 0; i < 8; i++)
	{
		winnings = SingleChipDrop(i, false);
		cout << "SingleChipDrop "<< i << ": " << winnings << endl;
	}

	// Test multiple chip drop
	cout << endl;
	srand(0);
	double average = 0.0;
	int chips = 10000;
	for (int x = 0; x < 10; x++)
	{
		for (int i = 0; i < 8; i++)
		{
			winnings = 0.0;
			MultipleChipDrop(chips, i, winnings);
			average = winnings / chips;
			if (average >= _averageValues[i][0] && average <= _averageValues[i][1])
				cout << "MultipleChipDrop: slot " << i << " OK: Winnings $" << winnings << ", average: $" << average << endl;
			else
				cout << "MultipleChipDrop: slot" << i << " NOT AVERAGE: Winnings $" << winnings << ", average: $" << average << endl;
		}
	}

	system("pause");
	return 0;
}

