#include "pch.h"
#include "CppUnitTest.h"
#include <stdexcept>

#include "ArrayClass.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab2unitTest
{
	TEST_CLASS(lab2unitTest)
	{
	public:

		Array* arr;

		// before each test
		TEST_METHOD_INITIALIZE(setUp)
		{
			arr = new Array('i', 10);
		}
		// after each test
		TEST_METHOD_CLEANUP(cleanUp)
		{
			delete arr;
		}
		
		TEST_METHOD(test_randomize)
		{
			arr->randomize();
			
			for (int i = 0; i < 10; i++)
			{
				Assert::IsTrue((arr->get('i', i) >= 0) && (arr->get('i', i) <= 5000));
			}
		}

		TEST_METHOD(test_possible_bin_search)
		{
			for (int i = 0; i < 10; i++)
			{
				arr->set(i, i, 'i');
			}

			bool found = arr->BinSearch(5);

			Assert::IsTrue(found);
		}

		TEST_METHOD(test_impossible_bin_search)
		{
			for (int i = 0; i < 10; i++)
			{
				arr->set(i, i, 'i');
			}

			bool found = arr->BinSearch(20);

			Assert::IsFalse(found);
		}

		TEST_METHOD(test_Qsort)
		{
			arr->randomize();
			arr->QSort();

			for (int i = 0; i < 10; i++)
			{
				Assert::IsTrue(arr->get('i', i) < arr->get('i', i+1));
			}
		}

		TEST_METHOD(test_insertion_sort)
		{
			arr->randomize();
			arr->InsertionSort();

			for (int i = 0; i < 10; i++)
			{
				Assert::IsTrue(arr->get('i', i) < arr->get('i', i + 1));
			}
		}

		TEST_METHOD(test_bogo_sort)
		{
			arr->randomize();
			arr->BogoSort();

			for (int i = 0; i < 10; i++)
			{
				Assert::IsTrue(arr->get('i', i) < arr->get('i', i + 1));
			}
		}

		TEST_METHOD(test_counting_sort)
		{
			Array core_arr('c', 25);

			char j = 'A';
			for (int i = 0; i < 25; i++)
			{
				core_arr.set(i, j, 'c');
				j++;
			}

			core_arr.randomize_char();
			core_arr.CountingSort();

			for (int i = 0; i < 25; i++)
			{
				Assert::IsTrue(core_arr.get('c', i) < core_arr.get('c', i + 1));
			}

			core_arr.~Array();
		}
	};
}
