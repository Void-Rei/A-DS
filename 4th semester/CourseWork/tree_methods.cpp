#include <stdexcept>
#include <iostream>
#include "tree.h"

using namespace std;

Tree::Tree()
{
	s = new Node('S');
	t = new Node('T');
}

Tree::Tree(Node* sourñe, Node* sink, size_t height)
{
	s = sourñe;
	s->height = height;
	t = sink;
}

Tree::~Tree()
{
	//clear();
	s = nullptr;
	t = nullptr;
}

void Tree::setHeight(size_t height)
{
	s->height = height;
}

bool Tree::contains(char targetLetter)
{
	Node* current;
	dft_Iterator* iterator = create_dft_Iterator();

	while (iterator->has_next()) // prevent out of bounds read
	{
		current = iterator->next();

		if (current->letter == targetLetter) { return true; }
	}

	return false;
}

void Tree::insert(char parentLetter, char newNodeLetter, unsigned capacityOfConnection) // insert new element 
{
	Node* current;
	dft_Iterator* iterator = create_dft_Iterator();

	while (iterator->has_next()) // prevent out of bounds read
	{
		current = iterator->next();

		if (current->letter == parentLetter)
		{
			if (parentLetter == 'S')
			{
				current = s;
			}

			if (current->left == nullptr)
			{
				if (newNodeLetter == 'T')
				{
					current->left = t;
				}
				else 
				{
					current->left = new Node(newNodeLetter); 
				}

				current->f.LeftCapacity = capacityOfConnection;
				break;
			}
			else if (current->right == nullptr)
			{
				if (newNodeLetter == 'T')
				{
					current->right = t;
				}
				else 
				{
					current->right = new Node(newNodeLetter); 
				}

				current->f.RightCapacity = capacityOfConnection;
				break;
			}
			else 
			{
				cout << "Error: parent node alredy has 2 connections" << endl;
				break;
			}
		}
	}
}

void Relabel(Node* u)
{
	size_t heightLeft = 0;
	size_t heightRight = 0;

	if ((u->left != nullptr) && ((u->f.LeftFlow - u->f.LeftCapacity) < 0))
	{
		heightLeft = u->left->height;
	}

	if ((u->right != nullptr) && ((u->f.RightFlow - u->f.RightCapacity) < 0))
	{
		heightRight = u->right->height;
	}

	u->height = min(heightLeft, heightRight) + 1;
}

void PushFlow(Node* u)
{
	if (u->left != nullptr)
	{
		if (u->height < u->left->height) { Relabel(u); }

		unsigned d = min(u->excess, (u->f.LeftCapacity - u->f.LeftFlow));
		u->f.LeftFlow += d;
		u->excess -= d;
		u->left->excess += d;
	}

	if (u->right != nullptr)
	{
		if (u->height < u->right->height) { Relabel(u); }

		unsigned d = min(u->excess, (u->f.RightCapacity - u->f.RightFlow));
		u->f.RightFlow += d;
		u->excess -= d;
		u->right->excess += d;
	}
}

unsigned Tree::Push_Relabel_maxFlow()
{
	s->f.LeftFlow = s->f.LeftCapacity;
	s->f.RightFlow = s->f.RightCapacity;
	s->left->excess = s->f.LeftCapacity;
	s->right->excess = s->f.RightCapacity;
	s->excess -= s->f.LeftCapacity + s->f.RightCapacity;
	
	Node* current = s;
	bool possibleToPush = true;
	dft_Iterator* iterator;

	while (possibleToPush)
	{
		iterator = create_dft_Iterator();
		iterator->next(); // skipping the source vertex - there's nothing to do with it

		while ((possibleToPush) && (iterator->has_next()))
		{
			current = iterator->next();

			if (current->excess > 0)
			{
				if ((current->f.LeftCapacity == current->f.LeftFlow) && (current->f.RightCapacity == current->f.RightFlow))
				{
					possibleToPush = false;
				}
				else { PushFlow(current); }
			}
		}

		if (possibleToPush)
		{
			iterator = create_dft_Iterator();
			iterator->next(); // skipping the source vertex - there's nothing to do with it

			do
			{
				current = iterator->next();
			} 
			while ((current->excess == 0 ) || (current == t));

			if (!iterator->has_next()) { return t->excess; }
		}
	}

	return t->excess;
}