#include <stdexcept>
#include <string>
#include <iostream>
#include "list_class.h"

using namespace std;

List::List()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

void List::reset_list()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
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

size_t List::get_size()
{
	return size;
}

void List::push_back(int newData)
{
	if (size == 0) {
		add_first(newData);
	}
	else {
		tail->next = new Node(newData);
		tail = tail->next;
	}
	size++;
}


void List::push_front(int newData)
{
	if (size == 0) {
		add_first(newData);
	}
	else {
		head = new Node(newData, head);
	}
	size++;

}

void List::pop_back()
{
	if (size == 0) return;

	if (size == 1) 
	{
		delete head;
		reset_list();
	}
	else {
		Node* current = head;
		while (current->next != tail) {
			current = current->next;
		}
		current->next = nullptr;
		delete tail;
		tail = current;
		current = nullptr;
	}
	size--;
}

void List::pop_front()
{
	if (size == 0) return;

	if (size == 1)
	{
		delete head;
		reset_list();
	}
	else
	{
		Node* newHead = head->next;
		delete head;
		head = newHead;
		newHead = nullptr;
	}
	size--;
}

void List::insert(int newData, size_t index)
{
	if (index > size) {
		throw out_of_range("Index is greater than list size");
	}
	
	else 
	{
		if ((index == 0) || (index == 1)) {
			push_front(newData);
		}

		else if (index == size) {
			push_back(newData);
		}

		else
		{
			Node* previous = head;
			Node* current = head->next;
			for (int i = 2; i != index; i++)
			{
				previous = previous->next;
				current = current->next;
			}
			Node* insNode = new Node(newData, current);
			previous->next = insNode;
			insNode = nullptr;
			previous = nullptr;
			current = nullptr;
		}
	}
	size++;
}

int List::at(size_t index) 
{
	if (index > size) {
		throw out_of_range("Index is greater than list size");
	}
	else {
		size_t counter = 0;
		Node* current = head;
		while (counter != index) {
			current = current->next;
			counter++;
		}
		return current->data;
	}
}

void List::remove(size_t index)
{
	if (index > size) {
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
			Node* current = head->next;
			for (int i = 2; i != index; i++)
			{
				previous = previous->next;
				current = current->next;
			}
			previous->next = current->next;
			delete current;
			previous = nullptr;
			current = nullptr;
		}
	}
	size--;
}

void List::print_to_console()
{
	Node* current = head;
	int i = 1;
	while (current != nullptr)
	{
		cout << "Node " << i << endl << current->data << endl;
		current = current->next;
		i++;
	}
}

void List::clear()
{
	Node* current = head;
	while (current != nullptr)
	{
		delete current;
		current = current->next;
	}
	reset_list();
}

void List::set(size_t index, int newData)
{
	Node* current = head;
	int i = 1;
	while (i != index)
	{
		current = current->next;
	}
	current->data = newData;
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
	tail->next = addition.head;
	tail = addition.tail;
}