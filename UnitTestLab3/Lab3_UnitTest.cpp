#include "pch.h"
#include "CppUnitTest.h"

#include "../alg_lab3/BinaryTree.h"
#include "../alg_lab3/Iterator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab3UnitTest
{
	TEST_CLASS(Lab3UnitTest)
	{
	public:
		
		BinarySearchTree* tree;

		TEST_METHOD_INITIALIZE(setUp)
		{
			tree = new BinarySearchTree();
		}

		TEST_METHOD_CLEANUP(cleanUp)
		{
			delete tree;
		}

		TEST_METHOD(contains_key_exist)
		{

			tree->insert(4);
			tree->insert(1);
			tree->insert(2);
			tree->insert(3);
			tree->insert(5);
			tree->insert(6);
			Assert::IsTrue(tree->contains(3));
		}
		TEST_METHOD(contains_key_doesnt_exist)
		{
			tree->insert(8);
			tree->insert(6);
			tree->insert(2);
			tree->insert(9);
			tree->insert(5);
			tree->insert(1);
			Assert::IsFalse(tree->contains(3));
		}
		TEST_METHOD(insert_empty_list)
		{
			tree->insert(1);
			Assert::IsTrue(tree->contains(1));
		}
		TEST_METHOD(insert_not_empty_tree)
		{
			tree->insert(8);
			tree->insert(6);

			tree->insert(1);
			Assert::IsTrue(tree->contains(1));
		}
		TEST_METHOD(insert_test)
		{
			tree->insert(9);
			tree->insert(10);
			tree->insert(6);
			tree->insert(8);
			tree->insert(4);

			tree->insert(5);
			Assert::IsTrue(tree->contains(5));
		}
		TEST_METHOD(remove_empty_tree)
		{
			try {
				tree->remove(5);
			}
			catch (std::out_of_range e) {
				Assert::AreEqual("The tree is empty", e.what());
			}
		}
		TEST_METHOD(remove_key_dosent_exist)
		{
			tree->insert(4);
			try {
				tree->remove(5);
			}
			catch (std::out_of_range e) {
				Assert::AreEqual("This key dosen't exist", e.what());
			}
		}
		TEST_METHOD(remove_not_empty_tree)
		{
			tree->insert(9);
			tree->insert(10);
			tree->insert(6);
			tree->insert(8);
			tree->insert(4);
			tree->insert(5);

			tree->remove(6);
			Assert::IsFalse(tree->contains(6));
		}
		TEST_METHOD(remove_root)
		{
			tree->insert(9);

			tree->remove(9);
			Assert::IsFalse(tree->contains(9));
		}
		TEST_METHOD(remove_leaf_nod)
		{
			tree->insert(5);
			tree->insert(2);
			tree->insert(7);
			tree->insert(6);
			tree->insert(8);

			tree->remove(6);
			Assert::IsFalse(tree->contains(6));
		}

		TEST_METHOD(remove_nod_have_one_child)
		{
			tree->insert(5);
			tree->insert(2);
			tree->insert(7);
			tree->insert(6);

			tree->remove(7);
			Assert::IsFalse(tree->contains(7));
		}
		TEST_METHOD(remove_nod_have_two_children)
		{
			tree->insert(5);
			tree->insert(2);
			tree->insert(7);
			tree->insert(6);
			tree->insert(8);

			tree->remove(7);
			Assert::IsFalse(tree->contains(7));
		}
		TEST_METHOD(bft_iterator)
		{
			int check_array[] = { 9, 6, 10, 4, 8, 5 };
			int index = 0;
			Iterator* bft_iterator;
			tree->insert(9);
			tree->insert(10);
			tree->insert(6);
			tree->insert(8);
			tree->insert(4);
			tree->insert(5);

			bft_iterator = tree->create_bft_iterator();
			while (bft_iterator->has_next()) {
				Assert::AreEqual(check_array[index], bft_iterator->next());
				index++;
			}
		}
		TEST_METHOD(dft_iterator)
		{
			int check_array[] = { 9, 10, 6, 8, 4, 5 };
			int index = 0;
			Iterator* dft_iterator;
			tree->insert(9);
			tree->insert(10);
			tree->insert(6);
			tree->insert(8);
			tree->insert(4);
			tree->insert(5);

			dft_iterator = tree->create_dft_iterator();
			while (dft_iterator->has_next()) {
				Assert::AreEqual(check_array[index], dft_iterator->next());
				index++;
			}
		}
	};
}
