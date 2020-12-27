#include <stdexcept>
#include <string>
#include <iostream>
#include "List.h"

using namespace std;

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
	delete head;
	delete tail;
	reset_list();
}

void List::add_first(int newData)
{
	head = new Node(newData);
	tail = head;
}

void List::add_first(char newData)
{
	head = new Node(newData);
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

void List::push_back(int newData)
{
	if (size == 0) {
		add_first(newData); // empty list -> create first Node
	}
	else {
		tail->next = new Node(newData); 
		tail = tail->next;
	}
	size++;
}

void List::push_back(char newData) //
{
	if (size == 0) {
		add_first(newData); // empty list -> create first Node
	}
	else {
		tail->next = new Node(newData);
		tail = tail->next;
	}
	size++;
}

bool List::check_type(size_t index)
{
	if ((index > size) || (index <= 0)) {
		throw out_of_range("Index is greater than list size");
	}
	else
	{
		size_t counter = 1;
		Node* current = head;
		
		while (counter != index) 
		{
			current = current->next;
			counter++;
		}

		if (current->c_data == 'i') {
			return true;
		}
		else { return false; }
	}
}

void List::print_to_console()
{
	Node* current = head;
	int i = 1;
	while (current != nullptr)
	{
		if (current->c_data == 'i') {
			cout << "Node " << i << "  Data: " << current->i_data << endl;
		}
		else { cout << "Node " << i << "  Data: " << current->c_data << endl; }
		
		current = current->next;
		i++;
	}
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
		while (current->next != tail) {
			current = current->next;   // finding pre-last Node 
		}
		current->next = nullptr; // deleting connection to tail
		delete tail;
		tail = current;
		current = nullptr;
	}
	size--;
}

void List::clear()
{
	while (size != 0)
	{
		pop_back();
	}
	reset_list();
}

bool List::isEmpty()
{
	if (size == 0) {
		return true;
	}
	else return false;
}