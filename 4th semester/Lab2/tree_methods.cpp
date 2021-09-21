#include <stdexcept>
#include <iostream>
#include "tree.h"
#include "list_class.h"
#include "node.h"

using namespace std;

Tree::Tree()
{
	root = nullptr;
}

Tree::Tree(Node* head)
{
	root = head;
}

Tree::~Tree()
{
	// clear();
	root = nullptr;
}

void Tree::setCodes(List* charList)
{
	dft_Iterator* dftIterator = create_dft_iterator();
	std::string currentCode = "";
	char currentLetter = '~';
	Node* currentNode = charList->get_head();
	size_t index = 0;

	while (dftIterator->has_next())
	{
		currentLetter = dftIterator->next();
		if (currentLetter != '~')
		{
			index = charList->find(currentLetter);
			charList->setCode(index, currentCode);
		}
	}
}