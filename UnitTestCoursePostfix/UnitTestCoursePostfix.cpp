#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>

#include "InfixToPosfix.h"
#include "List.h"
#include "Node.h"
#include "Stack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestCoursePostfix
{
	TEST_CLASS(UnitTestCoursePostfix)
	{
	public:
		
		TEST_METHOD(test_isEmpty_stack)
		{
			Stack test_stack;

			Assert::IsTrue(test_stack.isEmpty());
		}

		TEST_METHOD(test_push_stack)
		{
			Stack test_stack;
			Node* test_node_one = new Node(5);
			Node* test_node_two;

			test_stack.push(test_node_one);

			test_node_two = test_stack.getTop();

			Assert::IsTrue((test_node_one->i_data) == (test_node_two->i_data));
		}

		TEST_METHOD(test_pop_stack)
		{
			Stack test_stack;
			Node* test_node_one = new Node(5);
			Node* test_node_two;

			test_stack.push(test_node_one);

			test_node_two = test_stack.pop();

			Assert::IsTrue((test_node_one->i_data) == (test_node_two->i_data));
		}

		TEST_METHOD(test_push_back)
		{
			List* test_list = new List();

			test_list->push_back(1);
			test_list->push_back(2);

			test_list->pop_back();
			test_list->pop_back();

			Assert::IsTrue(test_list->isEmpty());
		}
	};
}
