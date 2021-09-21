#include <stdexcept>
#include <string>
#include <iostream>
#include "list_class.h"
#include "node.h"

using namespace std;

// list class uses the same node as the BinaryTree, 
// where next element is always on the left of current one

void List::reset_list()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}


List::List()
{
	reset_list();
}

List::~List()
{
	//clear();
	reset_list();
}

void List::add_first(char newLetter, unsigned newWeight)
{
	head = new Node(newLetter, newWeight);
	tail = head;
}

size_t List::get_size()
{
	return size;
}

Node* List::get_head()
{
	return head;
}

void List::push_back(char newLetter, unsigned newWeight)
{
	if (size == 0) {
		add_first(newLetter, newWeight); // empty list -> create first Node
	}
	else {
		tail->left = new Node(newLetter, newWeight); 
		tail = tail->left;
	}
	size++;
}


void List::push_front(char newLetter, unsigned newWeight) 
{
	if (size == 0) {
		add_first(newLetter, newWeight); // empty list -> create first Node
	}
	else {
		head = new Node(newLetter, newWeight, head);
	}
	size++;
}

void List::pop_back() 
{
	if (size == 0) return; // nothing to delete

	if (size == 1) 
	{
		delete head; // head == tail
		reset_list();
	}
	else {
		Node* current = head;
		while (current->left != tail) {
			current = current->left;   // finding pre-last Node 
		}
		current->left = nullptr; // deleting connection to tail
		delete tail;
		tail = current;			
		current = nullptr;
	}
	size--;
}

void List::pop_front() 
{
	if (size == 0) return; // nothing to delete

	if (size == 1)
	{
		delete head; // head == tail
		reset_list();
	}
	else
	{
		Node* newHead = head->left;
		delete head; 
		head = newHead;
		newHead = nullptr;
	}
	size--;
}

void List::insert(char newLetter, unsigned newWeight, size_t index)
{
	if ((index > size) || (index < 0)) {
		throw out_of_range("Index is out of list range");
	}
	
	else 
	{
		if ((index == 0) || (index == 1)) {
			push_front(newLetter, newWeight);
		}

		else if (index == size) {
			push_back(newLetter, newWeight);
		}

		else
		{
			Node* previous = head;
			Node* current = head->left;
			for (int i = 2; i != index; i++)
			{
				previous = previous->left;
				current = current->left;
			}
			Node* insNode = new Node(newLetter, newWeight, current);
			previous->left = insNode;
			insNode = nullptr;
			previous = nullptr;
			current = nullptr;
		}
	}
	size++;
}

size_t List::weightAt(size_t index) 
{
	if ((index > size) || (index < 0)) {
		throw out_of_range("Index is greater than list size");
	}
	else 
	{
		Node* current = head;

		for (size_t i = 1; i < index; i++)
		{
			current = current->left;
		}
		return current->weight;
	}
}

size_t List::find(char targetLetter) // finds node with given letter and returns it's index
{
	size_t counter = 1;
	Node* current = head;
	while (counter <= size) 
	{
		if (current->letter == targetLetter)
		{
			return counter;
		}
		current = current->left;
		counter++;
	}
	return 0;
}

void List::remove(size_t index)
{
	if ((index > size) || (index < 0)) {
		throw out_of_range("Index is greater than list size");
	}

	else
	{
		if ((index == 0) || (index == 1)) {
			pop_front();
		}

		else if (index == size) {
			pop_back();
		}

		else
		{
			Node* previous = head;
			Node* current = head->left;
			for (int i = 2; i != index; i++)
			{
				previous = previous->left;
				current = current->left;
			}
			previous->left = current->left;
			delete current;
			previous = nullptr;
			current = nullptr;
		}
	}
	size--;
}

unsigned List::print_to_console()
{
	Node* current = head;
	unsigned cypheredSize = 0;
	
	for (int i = 1; current != nullptr; i++)
	{
		cout << "|   " << current->letter << "   ";
		current = current->left;
	}

	cout << endl;
	current = head;

	for (int i = 1; current != nullptr; i++)
	{
		cout << "| ";
		if (current->weight < 10)
		{
			cout << "  " << current->weight << "  ";
		}
		else if (current->weight < 100)
		{
			cout << "  " << current->weight << " ";
		}
		else if (current->weight < 1000)
		{
			cout << " " << current->weight << " ";
		}
		else if (current->weight < 10000)
		{
			cout << " " << current->weight;
		}
		else
		{
			cout << current->weight;
		}
		
		cout << " ";
		current = current->left;
	}

	cout << endl;
	current = head;

	for (int i = 1; current != nullptr; i++)
	{
		cout << "| ";
		if (current->code.length() == 1)
		{
			cout << "  " << current->code.length() << "  ";
			cypheredSize++;
		}
		else if (current->code.length() == 2)
		{
			cout << "  " << current->code.length() << " ";
			cypheredSize += 2;
		}
		else if (current->code.length() == 3)
		{
			cout << " " << current->code.length() << " ";
			cypheredSize += 3;
		}
		else if (current->code.length() == 4)
		{
			cout << " " << current->code.length();
			cypheredSize += 4;
		}
		else
		{
			cout << current->code.length();
			cypheredSize = current->code.length() / 8;
		}

		cout << " ";
		current = current->left;
	}

	cout << endl;
	current = nullptr;
	return cypheredSize;
}

void List::clear()
{
	Node* current = head;
	Node* tmp;
	while (current != nullptr)
	{
		tmp = current;
		delete current;
		current = tmp->left;
		delete tmp;
	}
	reset_list();
}

void List::setLetter(size_t index, char newLetter)
{
	Node* current = head;
	int i = 1;
	while (i != index)
	{
		current = current->left;
	}
	current->letter = newLetter;
}

void List::setWeight(size_t index, size_t newWeight)
{
	Node* current = head;
	for (size_t i = 1; i < index; i++)
	{
		current = current->left;
	}
	current->weight = newWeight;
}

void List::setCode(size_t index, string newCode)
{
	Node* current = head;
	for (size_t i = 1; i < index; i++)
	{
		current = current->left;
	}
	current->code = newCode;
}

void List::minPair() // finds two minimal nodes, deletes them from available list, 
{					 // adds their created parent back to the list
	if (size > 1)
	{
		size_t minWeight = head->weight;
		size_t index = 1;
		size_t parentWeight = 2;

		Node* minNode1 = head;
		Node* minNode2 = nullptr;
		Node* current = head;

		/*Node* minPrev = nullptr;
		Node* minNext = head->left;*/

		for (size_t i = 1; i <= size; i++)
		{
			if (current->weight < minWeight)
			{
				index = i;
				minWeight = current->weight;
				minNode1 = current;
			}
			current = current->left;
		}

		remove(index);
		current = head;
		index = 1;

		for (size_t i = 1; i <= size; i++)
		{
			if (current->weight < minWeight)
			{
				index = i;
				minWeight = current->weight;
				minNode2 = current;
			}
			current = current->left;
		}

		if (minNode2 == nullptr) { minNode2 = head; }

		remove(index);

		parentWeight = minNode1->weight + minNode2->weight;
		push_back('~', parentWeight);

		tail->left = minNode1;
		tail->right = minNode2;

		//return true;
	}
	/*else
	{
		return false;
	}*/
}

void List::copy(List copyFrom)
{
	if (!copyFrom.isEmpty())
	{
		Node* current = copyFrom.head;

		for (size_t i = 1; i <= copyFrom.size; i++)
		{
			this->push_back(current->letter, current->weight);
			current = current->left;
		}

		current = nullptr;
	}
	else { throw range_error("Trying to copy from an empty file"); }
}

bool List::isEmpty()
{
	if (size == 0) {
		return true;
	}
	else return false;
}

void List::push_back(List addition)
{
	tail->left = addition.head;
	tail = addition.tail;
}