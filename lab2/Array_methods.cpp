#include <ctime>
#include <random>
#include <chrono>
#include <iostream>

#include "ArrayClass.h"

using namespace std;

Array::Array(char type, size_t in_size) :size(0)
{
	if (type == 'i') {
		A = new int[in_size]; // "type == i" means that user wants to create integer array
		C = nullptr;		// thus, we don't need the char pointer
	}
	else {
		C = new char[in_size]; // "type == c" means that user wants to create charecter array
		A = nullptr;
	}
	size = in_size;
}

Array::~Array()
{
	if (A != nullptr) // this way we understand what type is used
	{
		delete [] A;
		A = nullptr; // C is alredy a "nullptr" (see line 13)
		size = 0;
	}
	else 
	{
		delete [] C;
		C = nullptr; // A is alredy a "nullptr" (see line 17)
		size = 0;
	}
}

void Array::set(int key, size_t index, char type)
{
	if (type == 'i') {
		A[index] = key;
	}
	else {
		C[index] = key;
	}
}

int Array::get(char type, size_t i)
{
	if (type == 'i') {
		return A[i];
	}
	else {
		return C[i];
	}
}

void Array::randomize()
{
	mt19937 engine;
	const size_t seed = size_t(time(nullptr)); // generated seed based on time
	engine.seed(seed);

	for (size_t i = 0; i < size; i++)
	{
		// generated random distribution of numbers from 0 to (size - 1)
		uniform_int_distribution<size_t> distribution(0, 5000);

		A[i] = distribution(engine); // got one random number
	}
}

void Array::randomize_char()
{
	mt19937 engine;
	const size_t seed = size_t(time(nullptr)); // generated seed based on time
	engine.seed(seed);

	for (size_t i = 0; i < size; i++)
	{
		// generated random distribution of numbers from 0 to (size - 1)
		uniform_int_distribution<size_t> distribution(65, 90);

		A[i] = distribution(engine); // got one random number
	}
}

bool Array::BinSearch(int key) // Binary Search for A[]
{
	size_t min = 0, max = size - 1, middle; 
	
	while (!(min == max))
	{
		middle = min + (max - min) / 2;
		
		if (key == A[middle]) {
			return true;
		}
		else 
		{
			if (key < A[middle]) {
				max = middle;
			}

			else {
				min = middle;
			}
		}
	}
	return false;
}

void Array::qsrt(int left, int right) // recursive algorithm of Qsort
{
	int pivot; 
	int l_hold = left; 
	int r_hold = right; 
	pivot = A[left];
	while (left < right) 
	{
		while ((A[right] >= pivot) && (left < right))
			right--; 
		if (left != right) 
		{
			A[left] = A[right]; 
			left++;
		}
		while ((A[left] <= pivot) && (left < right))
			left++; 
		if (left != right) 
		{
			A[right] = A[left]; 
			right--; 
		}
	}
	A[left] = pivot;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) 
		qsrt(left, pivot - 1);
	if (right > pivot)
		qsrt(pivot + 1, right);

}

double Array::QSort() // shell of Qick Sort for A[]
{
	chrono::system_clock::time_point start = chrono::system_clock::now();
	chrono::system_clock::time_point end;
	chrono::duration<double> sec;

	qsrt(0, size-1);

	end = chrono::system_clock::now();
	sec = end - start;
	return sec.count();
}

double Array::InsertionSort() // Insertion Sort A[]
{
	chrono::system_clock::time_point start = chrono::system_clock::now();

	for (size_t i = 1; i < size; i++)
	{
		if (A[0] >= A[i])
		{
			int key = A[i];
			for (size_t j = i - 1; j != 0; j--) // moving every element to the right 
			{								// between A[i] (key) and A[0], excluding(!) both
				A[j + 1] = A[j];			
			}
			A[1] = key;
		}
		
		else
		{
			int key = A[i];
			for (size_t j = i - 1; j != 0; j--) // moving every element to the right 
			{								// from A[0] (including it) to A[i] key
				A[j + 1] = A[j];
			}
			A[1] = A[0];
			A[0] = key;
		}
	}
	
	chrono::system_clock::time_point end = chrono::system_clock::now();
	chrono::duration<double> sec = end - start;
	return sec.count();
}

void Array::BogoSort() // Random-based Sort for A[]
{
	mt19937 engine;
	const size_t seed = size_t(time(nullptr)); // generated seed based on time
	engine.seed(seed); 

	for (size_t i = 0; i < size; i++)
	{
		// generated random distribution of numbers from 0 to (size - 1)
		uniform_int_distribution<size_t> distribution(0, size - 1);

		swap(A[i], A[distribution(engine)]); // got one random index
	}

	for (size_t i = 0; i < size; i++)
	{
		if (A[i] < A[i + 1]) { continue; }

		else
		{
			BogoSort();
			return;
		}
	}
}

void Array::CountingSort() // Counting Sort for char C[]
{
	int max = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (A[i] > max) {
			max = A[i];  // finding maximum value
		}
	}
	
	max++; // adjusting to be correct size
	Array count('i', max); // auxilary array of indexes
	size_t k = 0;
	
	for (size_t i = 0; i < max; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (A[j] == i) { // counting occurences of certain numbers
				k++;
			}
		}
		count.A[i] = k; // saving times when certain number occured in corresponing element of index array
		k = 0;
	}

	size_t i = 0; // iterator of index in main array
	for (size_t j = 0; j < max; j++)
	{
		k = 0;
		while (k < count.A[j]) // write the same char 'k' times
		{
			A[i] = j;
			i++;
		}
	}
}
