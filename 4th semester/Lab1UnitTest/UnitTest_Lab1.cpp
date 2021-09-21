#include "pch.h"
#include "CppUnitTest.h"

#include "../Lab1/custom_map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab1UnitTest
{
	TEST_CLASS(Lab1UnitTest)
	{
	public:

		Map<char, int>* map;

		TEST_METHOD_INITIALIZE(setUp)
		{
			map = new Map<char, int>();
		}

		TEST_METHOD_CLEANUP(cleanUp)
		{
			delete map;
		}

		TEST_METHOD(insert_empty_tree)
		{
			map->insert('a', 1);
			Assert::IsTrue(map->find('a'));
		}
		TEST_METHOD(insert_not_empty_tree)
		{
			map->insert('h',8);
			map->insert('f',6);
			map->insert('a',1);
			Assert::IsTrue(map->find('a'));
		}
		TEST_METHOD(insert_test)
		{
			map->insert('i',9);
			map->insert('j',10);
			map->insert('f',6);
			map->insert('h',8);
			map->insert('d',4);

			map->insert('e',5);
			Assert::IsTrue(map->find('e'));
		}
		TEST_METHOD(find_key_exist)
		{

			map->insert('m', 13);
			map->insert('a', 1);
			map->insert('b', 2);
			map->insert('c', 3);
			map->insert('e', 5);
			map->insert('f', 6);
			Assert::IsTrue(map->find('c'));
		}
		TEST_METHOD(find_key_doesnt_exist)
		{
			map->insert('h',8);
			map->insert('f', 6);
			map->insert('b',2);
			map->insert('i',9);
			map->insert('e',5);
			map->insert('a',1);
			Assert::IsFalse(map->find('c'));
		}
		TEST_METHOD(remove_empty_tree)
		{
			try {
				map->remove('e');
			}
			catch (std::out_of_range e) {
				Assert::AreEqual("The map is empty", e.what());
			}
		}
		TEST_METHOD(remove_key_dosent_exist)
		{
			map->insert('d',4);
			try {
				map->remove('e');
			}
			catch (std::out_of_range e) {
				Assert::AreEqual("This key dosen't exist", e.what());
			}
		}
		TEST_METHOD(remove_not_empty_tree)
		{
			map->insert('i',9);
			map->insert('j',10);
			map->insert('f',6);
			map->insert('h',8);
			map->insert('d',4);
			map->insert('e',5);

			map->remove('f');
			Assert::IsFalse(map->find('f'));
		}
		TEST_METHOD(remove_root)
		{
			map->insert('i',9);

			map->remove('i');
			Assert::IsFalse(map->find('i'));
		}
		TEST_METHOD(remove_leaf_nod)
		{
			map->insert('e',5);
			map->insert('b',2);
			map->insert('g',7);
			map->insert('f',6);
			map->insert('h',8);

			map->remove('f');
			Assert::IsFalse(map->find('f'));
		}

		TEST_METHOD(remove_nod_have_one_child)
		{
			map->insert('e',5);
			map->insert('b',2);
			map->insert('g',7);
			map->insert('f',6);

			map->remove('g');
			Assert::IsFalse(map->find('g'));
		}
		TEST_METHOD(remove_nod_have_two_children)
		{
			map->insert('e',5);
			map->insert('b',2);
			map->insert('g',7);
			map->insert('f',6);
			map->insert('h',8);

			map->remove('g');
			Assert::IsFalse(map->find('g'));
		}
		TEST_METHOD(dft_iterator_test)
		{
			int check_array[] = { 9, 10, 6, 8, 4, 5 };
			int index = 0;
			MapNode<char, int>* current;
			map->insert('i',9);
			map->insert('j',10);
			map->insert('f',6);
			map->insert('h',8);
			map->insert('d',4);
			map->insert('e',5);

			dft_iterator* iterator = map->create_dft_iterator();
			while (iterator->has_next()) {
				current = iterator->next();
				Assert::AreEqual(check_array[index], current->value);
				index++;
			}
		}
	};
}
