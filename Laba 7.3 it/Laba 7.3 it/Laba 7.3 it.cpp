#include <iostream>
#include <iomanip>
#include <limits>
#include <unordered_map>
#include <time.h>

using namespace std;

void Input(int** a, const int rowCount, const int colCount);
void Create(int** arr, const int rowCount, const int colCount, const int Low,
	const int High);
void Print(int** a, const int rowCount, const int colCount);
int countNonZeroRows(int** arr, int rowCount, int colCount);
void findMaxDoubleValue(int** arr, const int rowCount, const int colCount, int& result);


int main() {

	srand((unsigned)time(NULL));

	int rowCount, colCount;
	int	maxDouble;
	int Low = 0;
	int High = 15;
	std::cout << "rowCount = "; std::cin >> rowCount;
	std::cout << "colCount = "; std::cin >> colCount;
	int** arr = new int* [rowCount];
	for (int i = 0; i < rowCount; i++)
		arr[i] = new int[colCount];

	//Input(arr, rowCount, colCount);
	Create(arr, rowCount, colCount, Low, High);
	Print(arr, rowCount, colCount);

	countNonZeroRows(arr, rowCount, colCount);
	findMaxDoubleValue( arr, rowCount, colCount, maxDouble);
	printf("Non zero rows: %d\n", countNonZeroRows(arr, rowCount, colCount));
	printf("Max double value: %d\n", maxDouble);

	for (int i = 0; i < rowCount; i++)
		delete[] arr[i];
	delete[] arr;
	return 0;
}

void Create(int** arr, const int rowCount, const int colCount, const int Low,
	const int High)
{
	for (int i = 0; i < rowCount; i++)
		for (int j = 0; j < colCount; j++)
			arr[i][j] = Low + rand() % (High - Low + 1);
}

void Input(int** arr, const int rowCount, const int colCount)
{
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			cout << "a[" << i << "][" << j << "] = ";
			cin >> arr[i][j];
		}
		cout << endl;
	}
}

void Print(int** arr, const int rowCount, const int colCount)
{
	cout << endl;
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
			cout << setw(4) << arr[i][j];
		cout << endl;
	}
	cout << endl;
}

int countNonZeroRows(int** arr, int rowCount, int colCount) {
	int result = rowCount;

	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			if (arr[i][j] == 0) {
				result--;
				break;
			}
		}
	}
	return result;
}

void findMaxDoubleValue(int** arr, const int rowCount, const int colCount, int& result) {
	// Хеш таблиця для запа'ятовування значень, які вже зустрічались хоч раз
	std::unordered_map<int, bool> cache;
	// Ініціалізуємо змінну для пошуку максимального значення
	int max = std::numeric_limits<int>::min();
	// Якщо після виконання функції залишиться false, то немає жодного значення, яке повторюється 
	bool foundDouble = false;

	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			int value = arr[i][j];
			// Якщо значення вже зустрічалось, та є більшим за теперішній максимум
			if (cache[value] && value > max) {
				max = value;
				foundDouble = true;
			}
			// Запам'ятовуєм, що ми вже зустрічали це значення
			cache[value] = true;
		}
	}
	// Записуєм результат по посиланю
	result = max;
}