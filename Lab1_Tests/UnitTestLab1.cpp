#include <stdexcept>

#include "CppUnitTest.h"
#include "../alg_lab1/list_class.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab1
{
	TEST_CLASS(Lab1UnitTests)
	{
	public:
		List* lst;

		// before each test
		TEST_METHOD_INITIALIZE(setUp)
		{
			lst = new List();
		}
		// after each test
		TEST_METHOD_CLEANUP(cleanUp)
		{
			delete lst;
		}
		
		TEST_METHOD(Insert_incorrect_index)
		{
			try {
				lst->insert(10, 5);
			}

			catch (std::out_of_range e) {
				Assert::AreEqual("Index is out of list range", e.what());
			}
		}

		TEST_METHOD(Insert_normal_index)
		{
			lst->push_back(1);
			lst->push_back(2);
			lst->push_back(4);
			lst->insert(3, 3);

			Assert::AreEqual(lst->at(3), 3);
		}

		TEST_METHOD(remove_incorrect_index)
		{
			try {
				lst->push_back(1);
				lst->push_back(2);
				lst->remove(10);
			}

			catch (std::out_of_range e) {
				Assert::AreEqual("Index is greater than list size", e.what());
			}
		}

		TEST_METHOD(remove_normal_index)
		{
			lst->push_back(1);
			lst->push_back(2);
			lst->push_back(3);
			lst->remove(2);

			Assert::AreEqual(lst->at(3), 3);
		}
	};
}
