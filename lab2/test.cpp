#include <iostream>
#include <ctime>
#include <random>
#include <chrono>

#include "ArrayClass.h"

using namespace std;

int main()
{
	size_t i;
	double QsortTime, QsortAverageTime, InsertionTime, InsertionAverageTime;

	for (i = 10; i <= 100000; i *= 10)
	{
		QsortTime = 0;
		QsortAverageTime = 0;
		InsertionTime = 0;
		InsertionAverageTime = 0;

		cout << "Sorting time for " << i << " elements" << endl;

		for (int j = 1; j <= 10; j++)
		{
			
			Array targetArray('i', i);
			targetArray.randomize();
			QsortTime = targetArray.QSort();

			targetArray.randomize();
			InsertionTime = targetArray.InsertionSort();

			cout << j << ") Qsort: " << QsortTime << " sec." << "|" << "Insertion sort : " << InsertionTime << " sec." << endl;

			QsortAverageTime += QsortTime;
			InsertionAverageTime += InsertionTime;
			targetArray.~Array();
		}

		cout << "Average time of Qsort: " << (QsortAverageTime / 10.0) << " sec." << endl << "Average time of Insertion sorting: " << InsertionAverageTime / 10 << " sec." << endl << endl;
	}
	return 1;
}