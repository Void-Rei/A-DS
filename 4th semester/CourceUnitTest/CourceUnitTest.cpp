#include "pch.h"
#include "CppUnitTest.h"
#include "node.h"
#include "tree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CourceUnitTest
{
	TEST_CLASS(CourceUnitTest)
	{
	public:
		
		Tree* net;

		TEST_METHOD_INITIALIZE(setUp)
		{
			net = new Tree();
		}

		TEST_METHOD_CLEANUP(cleanUp)
		{
			delete net;
		}

		TEST_METHOD(insert_empty_tree)
		{
			net->insert('S', 'T', 1);
			Assert::IsTrue(net->contains('a'));
		}
		TEST_METHOD(insert_not_empty_tree)
		{
			net->insert('S', 'O', 2);
			net->insert('O', 'T', 3);
			net->insert('S', 'K', 2);
			net->insert('K', 'T', 2);
			Assert::IsTrue(net->contains('T'));
		}
		TEST_METHOD(insert_test)
		{
			net->insert('S', 'O', 2);
			net->insert('O', 'T', 3);
			net->insert('S', 'K', 2);
			net->insert('K', 'M', 2);
			net->insert('M', 'T', 3);

			Assert::IsTrue(net->contains('M'));
		}

	};
}
