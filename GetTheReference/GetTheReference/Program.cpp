#include <iostream>

using namespace std;

void addFive(int* pNumber1, int* pNumber2, int* pNumber3)
{
	*pNumber1 += 5;
	*pNumber2 += 5;
	*pNumber3 += 5;
}

int main()
{
	int number1;
	int number2;
	int number3;

	cin >> number1;
	cin >> number2;
	cin >> number3;

	addFive(&number1, &number2, &number3);

	cout << number1 << endl;
	cout << number2 << endl;
	cout << number3 << endl;

	system("pause");

	return 0;
}