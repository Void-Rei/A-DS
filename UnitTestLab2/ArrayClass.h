#ifndef ARRAY_CLASS_H
#define ARRAY_CLASS_H

class Array
{
public:
	Array(char, size_t);

	void set(int, size_t, char); // sets data at certain index of array
	int get(char, size_t); // gets element of array
	void randomize(); // fills array with random values (0, 5000)
	void randomize_char(); // fills array with random values (0, 5000)
	bool BinSearch(int); // Binary Search
	void qsrt(int, int); // inside method of Qsort
	double QSort(); // Qick Sort
	double InsertionSort(); // Insertion Sort
	void BogoSort(); //Dull Sort
	void CountingSort(); // Counting Sort for char

	~Array();
private:
	int* A;
	char* C;
	size_t size;
};

#endif
